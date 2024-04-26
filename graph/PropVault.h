#ifndef GRAPH_EXTENSION_PROPVAULT_H
#define GRAPH_EXTENSION_PROPVAULT_H

#include "graph_types.h"
#include "strings_vault.h"
#include <string>
#include <iostream>

class PropVault {
public:
    PropVault(const std::string propFilename, const std::string strFilename);
    ~PropVault();

    bool isOpen() const;
    Prop getPropById(unsigned int id) const;
    VertexBody getPropsFromId(unsigned int id);

    void appendNewProp(const std::string& key, const std::string& value);
    void writePropBody(const VertexBody& body);
    void setProp(unsigned int propId, const std::string& value);

private:
    StringVault _vault;
    std::FILE *_file;
    unsigned int _currPropId = 0;
};


#endif //GRAPH_EXTENSION_PROPVAULT_H
