#ifndef EDGE_NODES_H
#define EDGE_NODES_H

#include "ast_node.h"
#include "label_node.h"
#include "object_name_node.h"
#include "vertices_list.h"
#include <iterator>

namespace cypher::tree {
    
    class edge_node : public ast_node {
    public:
        edge_node(object_name_node *name,
            label_node *label,
            vertices_list_node *rhs,
            vertices_list_node *lhs): _name(name), _label(label), _rhs(rhs), _lhs(lhs)
        {
            _childs.push_back(_name);
            _childs.push_back(_label);
            _childs.push_back(_rhs);
            _childs.push_back(_lhs);
        }

        void print() const override {
            std::cout << "Edge: " << std::endl;
            for (const auto p : _childs) {
                p->print();
                std::cout << std::endl;
            }
        }
    private:
        object_name_node *_name;
        label_node *_label;
        vertices_list_node *_rhs;
        vertices_list_node *_lhs;
    };

    class edges_list_node : public ast_node {
    public:
        edges_list_node(const std::vector<ast_node *>& list) {
            _type = ast_node_types::EDGES_LIST;
            std::copy(list.begin(), list.end(), std::back_inserter(_childs));
        }

        void print() const override {
            std::cout << "Edges list:" << std::endl;
            for (const auto p : _childs) {
                p->print();
                std::cout << std::endl;
            }
        }
    };
}

#endif
