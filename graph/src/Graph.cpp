#include "Graph.h"
#include <algorithm>
#include <iterator>

Graph::Graph(const std::string &strFilename, const std::string &propsFilename, const std::string &labelFilename,
             const std::string &edgesFilename, const std::string &nodesFilename) :
        _propVault(propsFilename, strFilename), _nodeVault(nodesFilename, edgesFilename), _labelVault(labelFilename),
        _currentNodeId(0), _currentEdgeId(0) {}

Graph::Graph(const std::string &strFilename, const std::string &propsFilename, const std::string &labelFilename,
             const std::string &edgesFilename, const std::string &nodesFilename, const GraphVertices &vertices,
             const GraphEgdes &edges) : Graph(strFilename, propsFilename, labelFilename, edgesFilename, nodesFilename) {
    _localEdges.resize(vertices.size());
    for (int i = 0; i < vertices.size(); ++i) {
        auto val = std::find_if(edges.begin(), edges.end(),
                                [&](const auto &e) { return e.first == vertices[i] || e.second == vertices[i]; });
        if (val != edges.end()) {
            _localNodes[i].nextEdgeId = std::distance(edges.begin(), val) + 1;
            _localNodes[i].body = vertices[i];
        }
    }

    _localEdges.resize(edges.size());
    auto rItt = _localEdges.begin();
    auto eItt = edges.begin();
    for (; rItt != _localEdges.end(); ++rItt, ++eItt) {
        auto firstVertex = std::find(vertices.begin(), vertices.end(), eItt->first);
        auto secondVertex = std::find(vertices.begin(), vertices.end(), eItt->second);
        (*rItt).firstNodeId = std::distance(vertices.begin(), firstVertex) + 1;
        (*rItt).lastNodeId = std::distance(vertices.begin(), secondVertex) + 1;

        auto revItt = std::make_reverse_iterator(eItt);
        auto prev = std::find_if(revItt, edges.rend(),
                                 [&](const auto &e) { return e.first == *firstVertex || e.second == *firstVertex; });
        if (prev != edges.rend()) {
            (*rItt).firstPrevEdge = std::distance(prev, edges.rend());
        }

        prev = std::find_if(revItt, edges.rend(),
                            [&](const auto &e) { return e.first == *secondVertex || e.second == *secondVertex; });
        if (prev != edges.rend()) {
            (*rItt).lastPrevEdge = std::distance(prev, edges.rend());
        }

        auto last = std::find_if(eItt + 1, edges.end(),
                                 [&](const auto &e) { return e.first == *firstVertex || e.second == *firstVertex; });
        if (last != edges.end()) {
            (*rItt).firstNextEdge = std::distance(edges.begin(), last) + 1;
        }

        last = std::find_if(eItt + 1, edges.end(),
                            [&](const auto &e) { return e.first == *secondVertex || e.second == *secondVertex; });
        if (last != edges.end()) {
            (*rItt).lastNextEdge = std::distance(edges.begin(), last) + 1;
        }
    }

    int i = 1;
    std::for_each(_localNodes.begin(), _localNodes.end(), [&](const auto &n) {
        _nodeVault.writeNodeToFile(i, static_cast<Node>(n));
        ++i;
    });
    _currentNodeId = i;
    i = 1;
    std::for_each(_localEdges.begin(), _localEdges.end(), [&](const auto &e) {
        _nodeVault.writeEdgeToFile(i, e);
        ++i;
    });
    _currentEdgeId = i;
}

MemoryNode Graph::getNodeById(unsigned int id) const {
    if (_localNodes.size() > id) {
        return _localNodes[id - 1];
    } else {
        auto n = _nodeVault.findNodeById(id);
        auto body = _propVault.getPropsFromId(n.firstPropId);
        MemoryNode res = {n.firstPropId, n.nextEdgeId, n.labelId, body};
        return res;
    }
}

Edge Graph::getEdgeById(unsigned int id) const {
    if (_localEdges.size() > id) {
        return _localEdges[id - 1];
    } else {
        auto e = _nodeVault.findEdgeById(id);
        return e;
    }
}

void Graph::updateNodeBody(unsigned int id, const MemoryNode &node) {
    if (_localNodes.size() > id) {
        _localNodes[id - 1] = node;
    }

    int oldSize = node.body.size();
    unsigned int curr_id = node.firstPropId;
    for (int i = 0; i < oldSize; ++i) {
        if (!curr_id) {
            _propVault.appendNewProp(node.body[i].first, node.body[i].second);
        } else {
            _propVault.setProp(curr_id, node.body[i].first, node.body[i].second);
            curr_id = _propVault.getPropById(curr_id).nextPropId;
        }
    }

    _nodeVault.writeNodeToFile(id, static_cast<Node>(node));

}

void Graph::deleteNode(unsigned int id) {
    unsigned int edgeId{};
    auto e = _nodeVault.findFirstEdgeForNode(id, &edgeId);
    if (e.firstNodeId) {
        while (e.firstNextEdge) {
            auto nextEdge = _nodeVault.findEdgeById(e.firstNextEdge);
            deleteEdge(edgeId);
            edgeId = e.firstNextEdge;
            e = nextEdge;
        }
    }

    _nodeVault.writeNodeToFile(id, Node{});
    auto removed = _localNodes.at(id - 1);
    auto newEnd = std::remove(_localNodes.begin(), _localNodes.end(), removed);
    _localNodes.erase(newEnd, _localNodes.end());
}

void Graph::deleteEdge(unsigned int id) {
    auto edge = _nodeVault.findEdgeById(id);
    Edge firstPrev{}, firstNext{};
    if (edge.firstPrevEdge)
        firstPrev = _nodeVault.getPrevForEdgeAndNode(id, edge.firstNodeId);
    if (edge.firstNextEdge)
        firstNext = _nodeVault.getNextForEdgeAndNode(id, edge.firstNodeId);

    if (firstNext.firstPrevEdge) {
        firstNext.firstPrevEdge = edge.firstPrevEdge;
        _nodeVault.writeEdgeToFile(edge.firstNextEdge, firstNext);
    }

    if (firstPrev.firstNextEdge) {
        firstPrev.firstNextEdge = edge.firstNextEdge;
        _nodeVault.writeEdgeToFile(edge.firstPrevEdge, firstPrev);
    }

    edge = Edge{};
    _nodeVault.writeEdgeToFile(id, edge);
    Edge removed = _localEdges.at(id - 1);
    auto newEnd = std::remove(_localEdges.begin(), _localEdges.end(), removed);
    _localEdges.erase(newEnd, _localEdges.end());
}

Edge Graph::appendNewEdge(const MemoryNode &first,
                          const MemoryNode &last, const std::string &label) {
    auto fstIter = std::find(_localNodes.begin(), _localNodes.end(), first);
    if (fstIter == _localNodes.end()) {
        throw std::logic_error{"Failed to find nodes in cache"};
    }
    unsigned int fstIdx = std::distance(_localNodes.begin(), fstIter) + 1;

    auto sndIter = std::find(_localNodes.begin(), _localNodes.end(), last);
    if (sndIter == _localNodes.end()) {
        throw std::logic_error{"Failed to find nodes in cache"};
    }
    unsigned int sndIdx = std::distance(_localNodes.begin(), sndIter) + 1;

    unsigned int labelId{};
    if (!label.empty()) {
        _labelVault.append(label);
        labelId = _labelVault.currentId();
    }

    Edge e{};
    e.labelId = labelId;
    e.firstNodeId = fstIdx;
    e.lastNodeId = sndIdx;

    unsigned int fstPrev = _nodeVault.findLastEdgeIndexForNode(fstIdx);
    unsigned int sndPrev = _nodeVault.findLastEdgeIndexForNode(sndIdx);

    e.firstPrevEdge = fstPrev;
    e.lastPrevEdge = sndPrev;

    _localEdges.push_back(e);
    _nodeVault.writeEdgeToFile(_currentEdgeId, e);
    ++_currentEdgeId;
    return e;
}

MemoryNode Graph::appendNewNode(const Vertex &vertex, const std::string &label) {
    unsigned int labelId{};
    if (!label.empty()) {
        _labelVault.append(label);
        labelId = _labelVault.currentId();
    }
    Node n = {_propVault.currentId() + 1, 0, labelId};
    _propVault.writePropBody(vertex);
    _nodeVault.writeNodeToFile(_currentNodeId, n);
    ++_currentNodeId;
    MemoryNode result{n.firstPropId, n.nextEdgeId, n.labelId, vertex};
    _localNodes.push_back(result);
    return result;
}

std::vector<Edge> Graph::getEdgesForNode(const MemoryNode &node) {
    std::vector<Edge> result;
    long index = 0;
    auto fstIter = std::find(_localNodes.begin(), _localNodes.end(), node);
    if (fstIter != _localNodes.end()) {
        index = std::distance(_localNodes.begin(), fstIter);
    } else {
        index = _nodeVault.getIndexByNode(static_cast<Node>(node));
    }
    auto tmpEdge = _nodeVault.findEdgeById(node.nextEdgeId);

    while (tmpEdge.firstNodeId == index || tmpEdge.lastNodeId == index) {
        result.push_back(tmpEdge);
        if (tmpEdge.firstNodeId == index || tmpEdge.firstNextEdge != 0) {
            tmpEdge = _nodeVault.findEdgeById(tmpEdge.firstNextEdge);
        } else if (tmpEdge.lastNodeId == index || tmpEdge.lastNextEdge != 0) {
            tmpEdge = _nodeVault.findEdgeById(tmpEdge.lastNextEdge);
        } else {
            break;
        }
    }
    return result;
}

std::vector<MemoryNode> Graph::getNodesByLabel(const std::string &label) {
    std::vector<MemoryNode> result;

    auto strId = _labelVault.findStr(label);
    if (!strId)
        return result;

    std::copy_if(_localNodes.begin(), _localNodes.end(), std::back_inserter(result),
                 [strId](const MemoryNode &m) {
                     return m.labelId == strId;
                 });

    auto fileNodes = _nodeVault.filterNodesByLabel(strId, (int) result.size());
    for (const auto &n: fileNodes) {
        VertexBody body = _propVault.getPropsFromId(n.firstPropId);
        result.emplace_back(n.firstPropId, n.nextEdgeId, n.labelId, body);
    }

    return result;
}

std::vector<Edge> Graph::getEdgesByLabel(const std::string &label) const {
    std::vector<Edge> result;

    auto strId = _labelVault.findStr(label);
    if (!strId)
        return result;

    std::copy_if(_localEdges.begin(), _localEdges.end(), std::back_inserter(result),
                 [strId](Edge e) {
                     return e.labelId == strId;
                 });

    auto fileEdges = _nodeVault.filterEdgesByLabel(strId, (int) result.size());
    std::copy(fileEdges.begin(), fileEdges.end(), std::back_inserter(result));
    return result;
}

std::vector<MemoryNode> Graph::getNodesContainsBody(const VertexBody &body) const {
    std::vector<MemoryNode> result;
    for (const auto &n: _localNodes) {
        if (std::search(n.body.begin(), n.body.end(),
                        body.begin(), body.end()) != n.body.end()) {
            result.push_back(n);
        }
    }
    return result;
}

