#pragma once

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
    unsigned int firstPropId;
    unsigned int nextEdgeId;
    unsigned int labelId;
};

struct Prop {
    unsigned int keyId;
    unsigned int valueId;
    unsigned int nextPropId;
} ;

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
    VertexBody body;
};
