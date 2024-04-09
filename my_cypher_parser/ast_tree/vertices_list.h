#ifndef VERTICES_LIST_NODE_H
#define VERTICES_LIST_NODE_H

#include "vertex_node.h"
#include <algorithm>

namespace cypher::tree {

    class vertices_list_node : public ast_node {
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

        void print(int tabs) const override {
            for(int i = 0; i < tabs; ++i)
                std::cout << " ";
            std::cout << "-- vertices list:" << std::endl;
            for (const auto p : _nodes) {
                p->print(tabs + 2);
            }
        }
    private:
        std::vector<std::shared_ptr<vertex_node>> _nodes;
    };
};

#endif
