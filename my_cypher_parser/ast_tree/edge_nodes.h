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
        { }

        void print(int tabs) const override {
            for(int i = 0; i < tabs; ++i)
                std::cout << " ";
            std::cout << "-- edge: " << std::endl;
            if(_name.has_value())
                _name.value()->print(tabs + 2);
            if(_label.has_value())
                _label.value()->print(tabs + 2);
            if(_rhs.has_value())
                _rhs.value()->print(tabs + 2);
            if(_lhs.has_value())
                _lhs.value()->print(tabs + 2);
        }
    private:
        name_opt _name;
        label_opt _label;
        list_opt _rhs;
        list_opt _lhs;
    };

    class edges_list_node : public ast_node {
    public:
        edges_list_node(const std::vector<std::shared_ptr<edge_node>>& list) {
            std::move(list.begin(), list.end(), std::back_inserter(_nodes));
        }

        void append(std::shared_ptr<edges_list_node>&& node) {
            std::move(node->_nodes.begin(), node->_nodes.end(), std::back_inserter(_nodes));
        }

        void append(std::shared_ptr<edge_node>&& node) {
            _nodes.emplace_back(std::move(node));
        }

        edges_list_node(std::shared_ptr<edges_list_node>&& node) {
            this->append(std::move(node));
        }

        void print(int tabs) const override {
            for(int i = 0; i < tabs; ++i)
                std::cout << " ";
            std::cout << "-- edges list:" << std::endl;
            for (const auto p : _nodes) {
                p->print(tabs + 2);
            }
        }
    private:
        std::vector<std::shared_ptr<edge_node>> _nodes;
    };
};

#endif
