//
// Created by dimonchik on 27.04.2024.
//

#include "NodeEdgeVault.h"

NodeEdgeVault::NodeEdgeVault(const std::string& nodesFilename, const std::string& edgesFilename) {
    if(!(_nodesFile = fopen(nodesFilename.c_str(), "w+"))) {
        throw std::logic_error("failed to open nodes file");
    }

    if(!(_edgesFile = fopen(edgesFilename.c_str(), "w+"))) {
        fclose(_nodesFile);
        throw std::logic_error("failed to open edges file");
    }
}

Node NodeEdgeVault::findNodeById(unsigned int id) const {
    if(std::fseek(_nodesFile, id * sizeof(Node), SEEK_SET) == -1) {
        char err[40];
        std::snprintf(err, 40, "Failed to find node with id %d\n", id);
        throw std::logic_error(err);
    }

    Node result;

    if(std::fread(&result, sizeof(Node), 1, _nodesFile) != 1) {
        char err[40];
        std::snprintf(err, 40, "Failed to read node with id %d\n", id);
        throw std::logic_error(err);
    }

    std::rewind(_nodesFile);
    return result;
}
void NodeEdgeVault::writeNodeToFile(unsigned int id, Node n) {
    std::fseek(_nodesFile, id * sizeof(Node), SEEK_SET);
    if(std::fwrite(&n, sizeof(Node), 1, _nodesFile) != 1) {
        char err[40];
        std::snprintf(err, 40, "Failed to write node with id %d\n", id);
        throw std::logic_error(err);
    }

    std::rewind(_nodesFile);
}

Edge NodeEdgeVault::findEdgeById(unsigned int id) const {
    if(std::fseek(_edgesFile, id * sizeof(Edge), SEEK_SET) == -1) {
        char err[40];
        std::snprintf(err, 40, "Failed to find edge with id %d\n", id);
        throw std::logic_error(err);
    }

    Edge result;
    if(std::fread(&result, sizeof(Edge), 1, _edgesFile) != 1) {
        char err[40];
        std::snprintf(err, 40, "Failed to read edge with id %d\n", id);
        throw std::logic_error(err);
    }

    std::rewind(_edgesFile);
    return result;
}
void NodeEdgeVault::writeEdgeToFile(unsigned int id, Node e) {
    std::fseek(_edgesFile, id * sizeof(Edge), SEEK_SET);
    if(std::fwrite(&e, sizeof(Edge), 1, _edgesFile) != 1) {
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