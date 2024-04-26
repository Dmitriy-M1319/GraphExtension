#include "graph_types.h"
#include "strings_vault.h"
#include <iostream>
#include <cstdio>


class PropVault {
public:
    PropVault(const std::string propFilename,
        const std::string strFilename): _vault(strFilename) {
        if(_vault.isVaultOpen() && (_file = std::fopen(propFilename.c_str(), "a+"))) {
            std::fseek(_file, 0, SEEK_END);
            long all_size = std::ftell(_file);
            _currPropId = all_size / sizeof(Prop);
        }
        std::cout << _currPropId << std::endl;
    }

    ~PropVault() {
        std::fclose(_file);
    }

    bool isOpen() const {
        return _file != NULL;
    }

    Prop getPropById(unsigned int id) const {
        Prop result{};

        if(std::fseek(_file, (id - 1) * sizeof(Prop), SEEK_SET) == -1) {
            std::cout << "seek fatal" << std::endl;
            return result;
        }
        
        if(std::fread(&result, sizeof(Prop), 1, _file) != 1) {
            std::cout << "read fatal" << std::endl;
            return result;
        }

        std::rewind(_file);
        return result;
    }

    // TODO: Переписать с использованием std::optional
    VertexBody getPropsFromId(unsigned int id) const {
        VertexBody result;
        
        Prop first_val = getPropById(id);
        if(first_val.keyId && first_val.valueId) {
            while(true) {
                auto key = _vault.getStrById(first_val.keyId);
                auto value = _vault.getStrById(first_val.valueId);
                result.push_back({key, value});

                if(first_val.nextPropId)
                    first_val = getPropById(first_val.nextPropId);
                else
                    break;
            }
        }

        return result;
    }

    void appendNewProp(const std::string& key, const std::string& value) {
        _vault.append(key);
        unsigned int keyId = _vault.currentId();
        _vault.append(value);
        unsigned int valueId = _vault.currentId();
        
        Prop newProp = {keyId, valueId};
        std::fseek(_file, 0, SEEK_END);
        std::fwrite(&newProp, sizeof(Prop), 1, _file);

        ++_currPropId;
        std::fseek(_file, sizeof(Prop) + 4, SEEK_END);
        std::fwrite(&_currPropId, sizeof(unsigned int), 1, _file);

        std::rewind(_file);
    }

    void writePropBody(const VertexBody& body) {
        for(const auto& p: body) {
            appendNewProp(p.first, p.second);
        }
    }

    void setProp(unsigned int propId, const std::string& value) {
        Prop updatedProp = getPropById(propId);
        if(updatedProp.valueId) {
            _vault.setStr(updatedProp.valueId, value);
        }
    }

private:
    StringVault _vault;
    std::FILE *_file;
    unsigned int _currPropId = 0;
};

void seedData() {
    Prop p1 {1, 2, 2};
    Prop p2 {3, 4, 3};
    Prop p3 {5, 6, 4};
    Prop p4 {7, 8, 0};

    std::FILE *f = std::fopen("prop_data.bin", "a");
    fwrite(&p1, sizeof(p1), 1, f);
    fwrite(&p2, sizeof(p1), 1, f);
    fwrite(&p3, sizeof(p1), 1, f);
    fwrite(&p4, sizeof(p1), 1, f);
    std::fclose(f);
}

int main(void) {
    PropVault val("prop_data.bin", "lines.txt");
    if(val.isOpen()) {
        auto body = val.getPropsFromId(1);
        for(const auto& p: body) {
            std::cout << "Key: " << p.first << " Value: " << p.second << std::endl;
        }
    } else {
        std::cout << "Vault is not open" << std::endl;
    }
    return 0; 
}
