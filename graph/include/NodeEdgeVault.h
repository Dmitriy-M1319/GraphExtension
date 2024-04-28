//
// Created by dimonchik on 27.04.2024.
//

#ifndef GRAPH_EXTENSION_NODEEDGEVAULT_H
#define GRAPH_EXTENSION_NODEEDGEVAULT_H

#include "GraphTypes.h"
#include <cstdio>
#include <string>

class NodeEdgeVault {
private:
    std::FILE *_nodesFile;
    std::FILE *_edgesFile;
public:
    NodeEdgeVault(const std::string& nodesFilename, const std::string& edgesFilename);
    Node findNodeById(unsigned int id) const;
    void writeNodeToFile(unsigned int id, Node n);

    Edge findEdgeById(unsigned int id) const;
    void writeEdgeToFile(unsigned int id, Edge e);

    ~NodeEdgeVault();
};


#endif //GRAPH_EXTENSION_NODEEDGEVAULT_H
