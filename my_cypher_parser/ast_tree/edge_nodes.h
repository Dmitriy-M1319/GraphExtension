#ifndef EDGE_NODES_H
#define EDGE_NODES_H

#include "ast_node.h"
#include "label_node.h"
#include "object_name_node.h"
#include "vertices_list.h"

namespace cypher::tree {
    
    class edge_node : public ast_node {
    public:
        edge_node(const object_name_node& name,
            const label_node& label,
            const vertices_list_node& rhs,
            const vertices_list_node& lhs,
            ast_node *parent): _name(name), _label(label), _rhs(rhs), _lhs(lhs)
        {
            _parent = parent;
            _childs.push_back(_name);
            _childs.push_back(_label);
            _childs.push_back(_rhs);
            _childs.push_back(_lhs);
        }

        void print() override {
            std::cout << "Edge: " << std::endl;
            for (auto& p : _childs) {
                p.print();
                std::cout << std::endl;
            }
        }
    private:
        object_name_node _name;
        label_node _label;
        vertices_list_node _rhs;
        vertices_list_node _lhs;
    };

    class edges_list : public ast_node {
    public:
        edges_list(const std::vector<edge_node>& list, ast_node *parent) {
            _parent = parent;
            _type = ast_node_types::EDGES_LIST;
            std::copy(list.begin(), list.end(), _childs.begin());
        }

        void print() override {
            std::cout << "Edges list:" << std::endl;
            for (auto& p : _childs) {
                p.print();
                std::cout << std::endl;
            }
        }
    };
}

#endif
