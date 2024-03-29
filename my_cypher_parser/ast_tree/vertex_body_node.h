#ifndef VERTEX_BODY_NODE_H
#define VERTEX_BODY_NODE_H

#include "key_value_node.h"
#include <algorithm>
#include <iterator>

namespace cypher::tree {
   
    class vertex_body_node : public ast_node {
    public:
        vertex_body_node(const std::vector<ast_node *>& list) {
            std::copy(list.begin(), list.end(), std::back_inserter(_childs));
        }

        void print() const override {
            std::cout << "Vertex key-value map:" << std::endl;
            for (const auto p : _childs) {
                p->print(); 
                std::cout << std::endl;
            }
        }
    };
};
#endif
