#pragma once

#include <vector>
#include <list>
#include <utility>
#include <string>

using graph_vertices = std::vector<std::string>;
using graph_egdes = std::vector<std::pair<std::string, std::string>>;
using key_value = std::pair<std::string, std::string>;
using vertex_body = std::list<key_value>;

struct node {
    unsigned int firstPropId;
    unsigned int nextEdgeId;
    unsigned int labelId;
};

typedef struct {
    unsigned int keyId;
    unsigned int valueId;
    unsigned int nextPropId;
} prop;

struct edge {
    unsigned int labelId;
    unsigned int firstNodeId;
    unsigned int lastNodeId;
    unsigned int firstPrevEdge;
    unsigned int lastPrevEdge;
    unsigned int firstNextEdge;
    unsigned int lastNextEdge;
};
