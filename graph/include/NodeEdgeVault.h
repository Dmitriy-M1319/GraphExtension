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
    NodeEdgeVault(const std::string &nodesFilename, const std::string &edgesFilename);

    [[nodiscard]] Node findNodeById(unsigned int id) const;

    void writeNodeToFile(unsigned int id, Node n);

    [[nodiscard]] Edge findEdgeById(unsigned int id) const;

    void writeEdgeToFile(unsigned int id, Edge e);

    Edge getPrevForEdgeAndNode(unsigned int edgeId, unsigned int nodeId) const;

    [[nodiscard]] Edge getNextForEdgeAndNode(unsigned int edgeId, unsigned int nodeId) const;

    [[nodiscard]] Edge findFirstEdgeForNode(unsigned int nodeId, unsigned int *outEdgeId) const;

    [[nodiscard]] unsigned int findLastEdgeIndexForNode(unsigned int nodeId) const;

    ~NodeEdgeVault();
};


#endif //GRAPH_EXTENSION_NODEEDGEVAULT_H
