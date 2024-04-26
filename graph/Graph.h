
#ifndef GRAPH_EXTENSION_GRAPH_H
#define GRAPH_EXTENSION_GRAPH_H

#include "graph_types.h"
#include "PropVault.h"

class Graph {
private:
    std::vector<MemoryNode> _localNodes;
    GraphEgdes _localEdges;
    PropVault _propVault;
    NodeEdgeVault _nodeVault;
public:
    Graph(std::string strFilename, std::string propsFilename);
    Graph(std::string strFilename, std::string propsFilename,
          const GraphVertices& vertices, const GraphEgdes& edges);

    MemoryNode getNodeById(unsigned int id);
    Edge getEdgeById(unsigned int id);

    void updateNodeBody(unsigned int id, const MemoryNode& node);
    void deleteNode(unsigned int id);
    void deleteEdge(unsigned int id);
};


#endif //GRAPH_EXTENSION_GRAPH_H
