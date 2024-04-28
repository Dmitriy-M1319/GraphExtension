
#ifndef GRAPH_EXTENSION_GRAPH_H
#define GRAPH_EXTENSION_GRAPH_H

#include "GraphTypes.h"
#include "NodeEdgeVault.h"
#include "PropVault.h"
#include <string>
#include <vector>

class Graph {
private:
    std::vector<MemoryNode> _localNodes;
    std::vector<Edge> _localEdges;
    PropVault _propVault;
    NodeEdgeVault _nodeVault;
public:
    Graph(const std::string& strFilename, const std::string& propsFilename,
          const std::string& edgesFilename, const std::string& nodesFilename);
    Graph(const std::string& strFilename, const std::string& propsFilename,
          const std::string& edgesFilename, const std::string& nodesFilename,
          const GraphVertices& vertices, const GraphEgdes& edges);

    MemoryNode getNodeById(unsigned int id);
    Edge getEdgeById(unsigned int id);

    void updateNodeBody(unsigned int id, const MemoryNode& node);
    void deleteNode(unsigned int id);
    void deleteEdge(unsigned int id);
};


#endif //GRAPH_EXTENSION_GRAPH_H
