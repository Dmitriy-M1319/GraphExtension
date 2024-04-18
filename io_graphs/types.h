#ifndef TYPES_H
#define TYPES_H

#include <stdio.h>

namespace graph {

struct Vertex {
    unsigned int nextEdge;
    unsigned int firstProp;
    unsigned int labelId;
};

struct Prop {
    unsigned int keyId;
    unsigned int valueId;
    unsigned int nextPropId;
};

struct Edge {
    unsigned int firstPrevEdge;
    unsigned int lastPrevEdge;
    unsigned int labelId;
    unsigned int firstNextEdge;
    unsigned int secondNextEdge;
};

int readVertex(unsigned int id, FILE *file, Vertex *v);
int readProp(unsigned int id, FILE *file, Prop *p);
int readEdge(unsigned int id, FILE *file, Edge *e);

};

#endif
