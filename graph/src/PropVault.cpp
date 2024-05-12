#include "PropVault.h"
#include <iostream>
#include <vector>

PropVault::PropVault(const std::string& propFilename,
          const std::string& strFilename): _vault(strFilename) {
    if(_vault.isVaultOpen() && (_file = std::fopen(propFilename.c_str(), "a+"))) {
        std::fseek(_file, 0, SEEK_END);
        long all_size = std::ftell(_file);
        _currPropId = all_size / sizeof(Prop);
    }
    std::cout << _currPropId << std::endl;
}

PropVault::~PropVault() {
    std::fclose(_file);
}

bool PropVault::isOpen() const {
    return _file != nullptr;
}

Prop PropVault::getPropById(unsigned int id) const {
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

VertexBody PropVault::getPropsFromId(unsigned int id) const {
    VertexBody result;

    Prop first_val = getPropById(id);
    if(first_val.keyId && first_val.valueId) {
        while(true) {
            auto key = _vault.getStrById(first_val.keyId);
            auto value = _vault.getStrById(first_val.valueId);
            result.emplace_back(key, value);

            if(first_val.nextPropId)
                first_val = getPropById(first_val.nextPropId);
            else
                break;
        }
    }

    return result;
}

void PropVault::appendNewProp(const std::string& key, const std::string& value) {
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

void PropVault::writePropBody(const VertexBody& body) {
    for(const auto& p: body) {
        appendNewProp(p.first, p.second);
    }
}

void PropVault::setProp(unsigned int propId,
                        const std::string& key,
                        const std::string& value) {
    Prop updatedProp = getPropById(propId);
    if(updatedProp.valueId) {
        _vault.setStr(updatedProp.keyId, key);
        _vault.setStr(updatedProp.valueId, value);
    }
}

unsigned int PropVault::currentId() const {
    return _currPropId;
}
