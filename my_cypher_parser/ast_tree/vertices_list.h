#ifndef VERTICES_LIST_NODE_H
#define VERTICES_LIST_NODE_H

#include "vertex_node.h"
#include "base_nodes.h"
#include <algorithm>

namespace cypher::tree {

    class vertices_list_node : public match_body_node {
    public:
        vertices_list_node(const std::vector<std::shared_ptr<vertex_node>>& list) {
            std::move(list.begin(), list.end(), std::back_inserter(_nodes));
        }

        void append(std::shared_ptr<vertices_list_node>&& node) {
            std::move(node->_nodes.begin(), node->_nodes.end(), std::back_inserter(_nodes));
        }

        void append(std::shared_ptr<vertex_node>&& node) {
            _nodes.emplace_back(std::move(node));
        }

        vertices_list_node(std::shared_ptr<vertices_list_node>&& node) {
            this->append(std::move(node));
        }

        void print() const override {
            std::cout << "Vertices list:" << std::endl;
            for (const auto p : _childs) {
                p->print();
                std::cout << std::endl;
            }
        }
    private:
        std::vector<std::shared_ptr<vertex_node>> _nodes;
    };
};

#endif
