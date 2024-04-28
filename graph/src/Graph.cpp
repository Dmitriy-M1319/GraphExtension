#include "Graph.h"
#include <algorithm>
#include <iterator>

Graph::Graph(const std::string& strFilename, const std::string& propsFilename,
             const std::string& edgesFilename, const std::string& nodesFilename):
             _propVault(propsFilename, strFilename), _nodeVault(nodesFilename, edgesFilename) {}

Graph::Graph(const std::string& strFilename, const std::string& propsFilename,
             const std::string& edgesFilename, const std::string& nodesFilename, const GraphVertices &vertices,
             const GraphEgdes &edges): Graph(strFilename, propsFilename, edgesFilename, nodesFilename) {
    _localEdges.resize(vertices.size());
    for(int i = 0; i < vertices.size(); ++i) {
        auto val = std::find_if(edges.begin(), edges.end(),
                                [&](const auto& e){ return e.first == vertices[i] || e.second == vertices[i]; });
        if(val != edges.end()) {
            _localNodes[i].nextEdgeId = std::distance(edges.begin(), val) + 1;
            _localNodes[i].body = vertices[i];
        }
    }

    _localEdges.resize(edges.size());
    auto rItt = _localEdges.begin();
    auto eItt = edges.begin();
    for(; rItt != _localEdges.end(); ++rItt, ++eItt) {
        auto firstVertex = std::find(vertices.begin(), vertices.end(), eItt->first);
        auto secondVertex = std::find(vertices.begin(), vertices.end(), eItt->second);
        (*rItt).firstNodeId = std::distance(vertices.begin(), firstVertex) + 1;
        (*rItt).lastNodeId = std::distance(vertices.begin(), secondVertex) + 1;

        auto revItt = std::make_reverse_iterator(eItt);
        auto prev = std::find_if(revItt, edges.rend(),
                                 [&](const auto& e){ return e.first == *firstVertex || e.second == *firstVertex; });
        if(prev != edges.rend()) {
            (*rItt).firstPrevEdge = std::distance(prev, edges.rend());
        }

        prev = std::find_if(revItt, edges.rend(),
                            [&](const auto& e){ return e.first == *secondVertex || e.second == *secondVertex; });
        if(prev != edges.rend()) {
            (*rItt).lastPrevEdge = std::distance(prev, edges.rend());
        }

        auto last = std::find_if(eItt + 1, edges.end(),
                                 [&](const auto& e){ return e.first == *firstVertex || e.second == *firstVertex; });
        if(last != edges.end()) {
            (*rItt).firstNextEdge = std::distance(edges.begin(), last) + 1;
        }

        last = std::find_if(eItt + 1, edges.end(),
                            [&](const auto& e){ return e.first == *secondVertex || e.second == *secondVertex; });
        if(last != edges.end()) {
            (*rItt).lastNextEdge = std::distance(edges.begin(), last) + 1;
        }
    }

    int i = 1;
    std::for_each(_localNodes.begin(), _localNodes.end(), [&](const auto& n) {
        _nodeVault.writeNodeToFile(i, static_cast<Node>(n));
        ++i;
    });
    i = 1;
    std::for_each(_localEdges.begin(), _localEdges.end(), [&](const auto& e) {
        _nodeVault.writeEdgeToFile(i, e);
        ++i;
    });

}

MemoryNode Graph::getNodeById(unsigned int id) {
    if(_localNodes.size() > id) {
        return _localNodes[id - 1];
    } else {
        auto n = _nodeVault.findNodeById(id);
        auto body = _propVault.getPropsFromId(n.firstPropId);
        MemoryNode res = {n.firstPropId, n.nextEdgeId, n.labelId, body};
        return res;
    }
}

Edge Graph::getEdgeById(unsigned int id) {
    if(_localEdges.size() > id) {
        return _localEdges[id - 1];
    } else {
        auto e = _nodeVault.findEdgeById(id);
        return e;
    }
}

void Graph::updateNodeBody(unsigned int id, const MemoryNode &node) {
    if(_localNodes.size() > id) {
        _localNodes[id - 1] = node;
    }

    int oldSize = node.body.size();
    unsigned int curr_id = node.firstPropId;
    for(int i = 0; i < oldSize; ++i) {
        if(!curr_id) {
            _propVault.appendNewProp(node.body[i].first, node.body[i].second);
        } else {
            _propVault.setProp(curr_id, node.body[i].first, node.body[i].second);
            curr_id = _propVault.getPropById(curr_id).nextPropId;
        }
    }

    _nodeVault.writeNodeToFile(id, static_cast<Node>(node));

}

void Graph::deleteNode(unsigned int id) {

}

void Graph::deleteEdge(unsigned int id) {

}
