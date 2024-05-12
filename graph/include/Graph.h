
#ifndef GRAPH_EXTENSION_GRAPH_H
#define GRAPH_EXTENSION_GRAPH_H

#include "GraphTypes.h"
#include "NodeEdgeVault.h"
#include "PropVault.h"
#include <string>
#include <vector>

/*
 * TODO: Написать функции поиска всех ребер для узла в кеше и файле
 * TODO: Написать поиск узлов по содержимому тела
 * TODO: Написать фильтрацию всех ребер по определенным узлам и меткам
 */

class Graph {
private:
    std::vector<MemoryNode> _localNodes;
    std::vector<Edge> _localEdges;
    PropVault _propVault;
    NodeEdgeVault _nodeVault;
    unsigned int _currentNodeId;
    unsigned int _currentEdgeId;
    StringVault _labelVault;
public:
    Graph(const std::string &strFilename, const std::string &propsFilename,
          const std::string &labelFilename, const std::string &edgesFilename, const std::string &nodesFilename);

    Graph(const std::string &strFilename, const std::string &propsFilename,
          const std::string &labelFilename, const std::string &edgesFilename, const std::string &nodesFilename,
          const GraphVertices &vertices, const GraphEgdes &edges);

    std::vector<Edge> getEdgesForNode(const MemoryNode &node) const;

    std::vector<MemoryNode> getNodesByLabel(const std::string &label) const;

    std::vector<Edge> getEdgesByLabel(const std::string &label) const;

    std::vector<MemoryNode> getNodesContainsBody(VertexBody body) const;

    MemoryNode getNodeById(unsigned int id) const;

    Edge getEdgeById(unsigned int id) const;

    MemoryNode appendNewNode(const Vertex &vertex, const std::string &label = "");

    Edge appendNewEdge(const MemoryNode &first,
                       const MemoryNode &last, const std::string &label = "");

    void updateNodeBody(unsigned int id, const MemoryNode &node);

    void deleteNode(unsigned int id);

    void deleteEdge(unsigned int id);
};


#endif //GRAPH_EXTENSION_GRAPH_H
