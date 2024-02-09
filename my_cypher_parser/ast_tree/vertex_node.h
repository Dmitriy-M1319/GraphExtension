#ifndef VERTEX_NODE_H
#define VERTEX_NODE_H

#include "label_node.h"
#include "object_name_node.h"
#include "vertex_body_node.h"
#include <optional>

namespace cypher::tree {
    class vertex_node : public ast_node {
    public:
        vertex_node(std::optional<vertex_body_node *> body, 
                label_node *label,
                object_name_node *name): _body{body}, _label{label}, _name{name} 
        {
            _type = ast_node_types::VERTEX;
            _childs.push_back(name);
            _childs.push_back(label);
            if(body) {
                _childs.push_back(body.value());
            }
        }

        void print() const override {
            std::cout << "Vertex" << std::endl;
            for (const auto p : _childs) {
                p->print(); 
            }
        }
    private:
        std::optional<vertex_body_node *> _body;
        label_node *_label;
        object_name_node *_name;
    };
}

#endif
