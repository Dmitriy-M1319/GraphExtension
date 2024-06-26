//
// Created by dimonchik on 27.04.2024.
//

#include "NodeEdgeVault.h"
#include <stdexcept>

NodeEdgeVault::NodeEdgeVault(const std::string &nodesFilename, const std::string &edgesFilename) {
    if (!(_nodesFile = fopen(nodesFilename.c_str(), "w+"))) {
        throw std::logic_error("failed to open nodes file");
    }

    if (!(_edgesFile = fopen(edgesFilename.c_str(), "w+"))) {
        fclose(_nodesFile);
        throw std::logic_error("failed to open edges file");
    }

    std::fseek(_nodesFile, 0, SEEK_END);
    _nodesCount = (int)(ftell(_nodesFile) / sizeof (Node));
    fseek(_nodesFile, 0, SEEK_SET);

    std::fseek(_edgesFile, 0, SEEK_END);
    _edgesCount = (int)(ftell(_edgesFile) / sizeof (Edge));
    fseek(_edgesFile, 0, SEEK_SET);
}

Node NodeEdgeVault::findNodeById(unsigned int id) const {
    Node result{};
    if (std::fseek(_nodesFile, id * long(sizeof(Node)), SEEK_SET) == -1) {
        char err[40];
        std::snprintf(err, 40, "Failed to find node with id %d\n", id);
        throw std::logic_error(err);
    }

    if (std::fread(&result, sizeof(Node), 1, _nodesFile) != 1) {
        char err[40];
        std::snprintf(err, 40, "Failed to read node with id %d\n", id);
        throw std::logic_error(err);
    }

    std::rewind(_nodesFile);
    return result;
}

void NodeEdgeVault::writeNodeToFile(unsigned int id, Node n) {
    std::fseek(_nodesFile, id * long(sizeof(Node)), SEEK_SET);
    if (std::fwrite(&n, sizeof(Node), 1, _nodesFile) != 1) {
        char err[40];
        std::snprintf(err, 40, "Failed to write node with id %d\n", id);
        throw std::logic_error(err);
    }

    std::rewind(_nodesFile);
}

Edge NodeEdgeVault::findEdgeById(unsigned int id) const {
    if (std::fseek(_edgesFile, id * long(sizeof(Edge)), SEEK_SET) == -1) {
        char err[40];
        std::snprintf(err, 40, "Failed to find edge with id %d\n", id);
        throw std::logic_error(err);
    }

    Edge result{};
    if (std::fread(&result, sizeof(Edge), 1, _edgesFile) != 1) {
        char err[40];
        std::snprintf(err, 40, "Failed to read edge with id %d\n", id);
        throw std::logic_error(err);
    }

    std::rewind(_edgesFile);
    return result;
}

void NodeEdgeVault::writeEdgeToFile(unsigned int id, Edge e) {
    std::fseek(_edgesFile, id * long(sizeof(Edge)), SEEK_SET);
    if (std::fwrite(&e, sizeof(Edge), 1, _edgesFile) != 1) {
        char err[40];
        std::snprintf(err, 40, "Failed to write edge with id %d\n", id);
        throw std::logic_error(err);
    }

    std::rewind(_edgesFile);
}

NodeEdgeVault::~NodeEdgeVault() {
    fclose(_nodesFile);
    fclose(_edgesFile);
}

Edge NodeEdgeVault::getPrevForEdgeAndNode(unsigned int edgeId, unsigned int nodeId) const {
    auto currEdge = findEdgeById(edgeId);
    if (currEdge.firstNodeId != nodeId && currEdge.lastNodeId != nodeId)
        throw std::logic_error("Edge doesn't include this node id!");

    if (currEdge.firstNodeId == nodeId) {
        return findEdgeById(currEdge.firstPrevEdge);
    } else {
        return findEdgeById(currEdge.lastPrevEdge);
    }
}

Edge NodeEdgeVault::getNextForEdgeAndNode(unsigned int edgeId, unsigned int nodeId) const {
    auto currEdge = findEdgeById(edgeId);
    if (currEdge.firstNodeId != nodeId && currEdge.lastNodeId != nodeId)
        throw std::logic_error("Edge doesn't include this node id!");

    if (currEdge.firstNodeId == nodeId) {
        return findEdgeById(currEdge.firstNextEdge);
    } else {
        return findEdgeById(currEdge.lastNextEdge);
    }
}

Edge NodeEdgeVault::findFirstEdgeForNode(unsigned int nodeId, unsigned int *outEdgeId) const {
    Edge result{};
    *outEdgeId = 0;
    if (!nodeId)
        return result;
    auto n = findNodeById(nodeId);
    result = findEdgeById(n.nextEdgeId);
    *outEdgeId = n.nextEdgeId;
    return result;
}

unsigned int NodeEdgeVault::findLastEdgeIndexForNode(unsigned int nodeId) const {
    unsigned int result{};
    auto n = findNodeById(nodeId);
    auto currentEdge = findEdgeById(n.nextEdgeId);
    if((currentEdge.firstNodeId == nodeId && !currentEdge.firstNextEdge) ||
           (currentEdge.lastNodeId == nodeId && !currentEdge.lastNextEdge)) {
        return n.nextEdgeId;
    }

    while ((currentEdge.firstNodeId == nodeId && currentEdge.firstNextEdge) ||
           (currentEdge.lastNodeId == nodeId && currentEdge.lastNextEdge)) {
        if (currentEdge.firstNodeId == nodeId) {
            result = currentEdge.firstNextEdge;
            currentEdge = findEdgeById(currentEdge.firstNextEdge);
        } else {
            result = currentEdge.lastNextEdge;
            currentEdge = findEdgeById(currentEdge.lastNextEdge);
        }
    }
    return result;
}

std::vector<Node> NodeEdgeVault::filterNodesByLabel(unsigned int labelId, int offset) const {
    std::vector<Node> result;
    unsigned int startId = offset + 1;
    for(; startId != _nodesCount; ++startId) {
        auto n = findNodeById(startId);
        if(n.labelId == labelId)
            result.push_back(n);
    }
    return result;
}

std::vector<Edge> NodeEdgeVault::filterEdgesByLabel(unsigned int labelId, int offset) const {
    std::vector<Edge> result;
    unsigned int startId = offset + 1;

    for(; startId != _edgesCount; ++startId) {
        auto e = findEdgeById(startId);
        if(e.labelId == labelId)
            result.push_back(e);
    }
    return result;
}

unsigned int NodeEdgeVault::getIndexByNode(Node node) const {
    Node curr;
    for(unsigned int i = 1; i != _edgesCount; ++i) {
        curr = findNodeById(i);
        if(curr == node)
           return i;
    }
    return 0;
}
