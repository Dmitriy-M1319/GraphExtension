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
        using list_opt = std::optional<std::shared_ptr<vertices_list_node>>;
        using label_opt = std::optional<std::shared_ptr<label_node>>;
        using name_opt = std::optional<std::shared_ptr<object_name_node>>;

        edge_node(name_opt&& name,
            label_opt&& label,
            list_opt&& rhs,
            list_opt&& lhs): _name(std::move(name)), _label(std::move(label)), _rhs(std::move(rhs)), _lhs(std::move(lhs))
        { /* потом подумать над детьми */ }

        void print() const override {
            std::cout << "Edge: " << std::endl;
            for (const auto p : _childs) {
                p->print();
                std::cout << std::endl;
            }
        }
    private:
        name_opt _name;
        label_opt _label;
        list_opt _rhs;
        list_opt _lhs;
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
