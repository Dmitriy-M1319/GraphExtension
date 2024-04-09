#ifndef VERTEX_NODE_H
#define VERTEX_NODE_H

#include "ast_node.h"
#include "label_node.h"
#include "object_name_node.h"
#include "vertex_body_node.h"
#include <optional>

namespace cypher::tree {
    class vertex_node : public ast_node {
    public:
        using body_opt = std::optional<std::shared_ptr<vertex_body_node>>;
        using label_opt = std::optional<std::shared_ptr<label_node>>;
        using name_opt = std::optional<std::shared_ptr<object_name_node>>;

        vertex_node(): ast_node(), _body{std::nullopt}, _label{std::nullopt}, _name{std::nullopt} {}

        vertex_node(body_opt&& body, 
                label_opt&& label,
                name_opt&& name): _body{std::move(body)}, _label{std::move(label)}, _name{std::move(name)} 
        {
            _type = ast_node_types::VERTEX;
        }

        void print(int tabs) const override {
            for(int i = 0; i < tabs; ++i)
                std::cout << " ";
            std::cout << "-- vertex:" << std::endl;
            if(_name.has_value()) 
                _name.value()->print(tabs + 2);
            if(_label.has_value())
                _label.value()->print(tabs + 2);
            if(_body.has_value())
                _body.value()->print(tabs + 2);
        }
    private:
        body_opt _body;
        label_opt _label;
        name_opt _name;
    };
};

#endif
