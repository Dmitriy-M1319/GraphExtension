#ifndef VERTICES_LIST_NODE_H
#define VERTICES_LIST_NODE_H

#include "vertex_node.h"
#include "base_nodes.h"

namespace cypher::tree {

    class vertices_list_node : public match_body_node {
    public:
        vertices_list_node(const std::vector<vertex_node *>& list) {
            _type = ast_node_types::VERTICES_LIST;
            std::copy(list.begin(), list.end(), _childs.begin());
        }

        void print() const override {
            std::cout << "Vertices list:" << std::endl;
            for (const auto p : _childs) {
                p->print();
                std::cout << std::endl;
            }
        }
    };
};

#endif
