#include "graph_types.h"
#include <cstdio>
#include <cstdlib>

int findEdgeById(unsigned int id, std::FILE *edgeFile, Edge *ePtr) {
    if(edgeFile == nullptr || ePtr == nullptr)
        return -1;
        
    if(std::fseek(edgeFile, id * sizeof(Edge), SEEK_SET) == -1) {
        std::fprintf(stderr, "Failed to find edge with id %d\n", id);
        return -1;
    }

    if(std::fread(ePtr, sizeof(Edge), 1, edgeFile) != 1) {
        std::fprintf(stderr, "Failed to read edge with id %d\n", id);
        return -1;
    }

    std::rewind(edgeFile);
    return 0;

}

int writeEdgeToFile(unsigned int id, std::FILE *edgeFile, Node *ePtr) {
    if(edgeFile == nullptr || ePtr == nullptr)
        return -1;
    std::fseek(edgeFile, id * sizeof(Edge), SEEK_SET);
    if(std::fwrite(ePtr, sizeof(Edge), 1, edgeFile) != 1) {
        std::fprintf(stderr, "Failed to write edge with id %d\n", id);
        return -1;
    }

    std::rewind(edgeFile);
    return 0;
    
}

int findNodeById(unsigned int id, std::FILE *nodeFile, Node *nPtr) {
    if(nodeFile == nullptr || nPtr == nullptr)
        return -1;
        
    if(std::fseek(nodeFile, id * sizeof(Node), SEEK_SET) == -1) {
        std:fprintf(stderr, "Failed to find node with id %d\n", id);
        return -1;
    }

    if(std::fread(nPtr, sizeof(Node), 1, nodeFile) != 1) {
        std::fprintf(stderr, "Failed to read node with id %d\n", id);
        return -1;
    }

    std::rewind(nodeFile);
    return 0;

}

int writeNodeToFile(unsigned int id, std::FILE *nodeFile, Node *nPtr) {
    if(nodeFile == nullptr)
        return -1;
    std::fseek(nodeFile, id * sizeof(Node), SEEK_SET);
    if(std::fwrite(nPtr, sizeof(Node), 1, nodeFile) != 1) {
        std::fprintf(stderr, "Failed to write node with id %d\n", id);
        return -1;
    }

    std::rewind(nodeFile);
    return 0;
    
}

int main(void) {
    std::FILE *f = std::fopen("data.bin", "w+");
    Node n = {1, 4, 3};
    if(writeNodeToFile(0, f, &n) < 0) {
        std::puts("Failed to write file");
        std::fclose(f);
        return -1;
    }
    if(writeNodeToFile(1, f, &n) < 0) {
        std::puts("Failed to write file");
        std::fclose(f);
        return -1;
    }
    if(writeNodeToFile(2, f, &n) < 0) {
        std::puts("Failed to write file");
        std::fclose(f);
        return -1;
    }
    if(writeNodeToFile(3, f, &n) < 0) {
        std::puts("Failed to write file");
        std::fclose(f);
        return -1;
    }
    if(writeNodeToFile(4, f, &n) < 0) {
        std::puts("Failed to write file");
        std::fclose(f);
        return -1;
    }
    Node *nPtr = (Node *)std::malloc(sizeof(Node));
    if(findNodeById(4, f, nPtr) < 0) {
        std::puts("Failed to read file");
        std::fclose(f);
        std::free(nPtr);
        return -1;
    }

    std::printf("Struct node: %d, %d, %d\n", nPtr->firstPropId, nPtr->nextEdgeId, nPtr->labelId);
    std::fclose(f);
    std::free(nPtr);
    return 0;
}
