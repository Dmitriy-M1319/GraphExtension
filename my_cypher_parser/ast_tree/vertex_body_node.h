#ifndef VERTEX_BODY_NODE_H
#define VERTEX_BODY_NODE_H

#include "key_value_node.h"
#include <algorithm>

namespace cypher::tree {
   
    class vertex_body_node : public ast_node {
    public:
        vertex_body_node(const std::vector<std::shared_ptr<key_value_node>>& list) {
            std::move(list.begin(), list.end(), std::back_inserter(_nodes));
        }

        void append(std::shared_ptr<vertex_body_node>&& node) {
            std::move(node->_nodes.begin(), node->_nodes.end(), std::back_inserter(_nodes));
        }

        void append(std::shared_ptr<key_value_node>&& node) {
            _nodes.emplace_back(std::move(node));
        }

        vertex_body_node(std::shared_ptr<vertex_body_node>&& node) {
            this->append(std::move(node));
        }

        void print() const override {
            std::cout << "Vertex key-value map:" << std::endl;
            for (const auto p : _nodes) {
                p.get()->print(); 
                std::cout << std::endl;
            }
        }
    private:
        std::vector<std::shared_ptr<key_value_node>> _nodes;
    };
};
#endif
