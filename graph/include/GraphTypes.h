#pragma once

#include <utility>
#include <vector>
#include <list>
#include <utility>
#include <string>

using KeyValue = std::pair<std::string, std::string>;
using VertexBody = std::vector<KeyValue>;
using Vertex = VertexBody;
using GraphVertices = std::vector<Vertex>;
using GraphEgdes = std::vector<std::pair<Vertex, Vertex>>;


struct Node {
public:
    unsigned int firstPropId{};
    unsigned int nextEdgeId{};
    unsigned int labelId{};

    Node() = default;

    Node(unsigned int firstPropId, unsigned int nextEdgeId,
         unsigned int labelId) : firstPropId(firstPropId), labelId(labelId),
                                 nextEdgeId(nextEdgeId) {}
};

struct Prop {
    unsigned int keyId;
    unsigned int valueId;
    unsigned int nextPropId;
};

struct Edge {
    unsigned int labelId;
    unsigned int firstNodeId;
    unsigned int lastNodeId;
    unsigned int firstPrevEdge;
    unsigned int lastPrevEdge;
    unsigned int firstNextEdge;
    unsigned int lastNextEdge;
};

struct MemoryNode : public Node {
public:
    VertexBody body;

    MemoryNode(unsigned int firstPropId, unsigned int nextEdgeId,
               unsigned int labelId, VertexBody body) :
            Node(firstPropId, nextEdgeId, labelId), body(std::move(body)) {
    }

    bool operator==(const MemoryNode &node) {
        return firstPropId == node.firstPropId && nextEdgeId == node.nextEdgeId &&
               labelId == node.labelId && body == node.body;
    }
};
