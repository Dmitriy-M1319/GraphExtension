#ifndef LABEL_NODE_H
#define LABEL_NODE_H

#include "ast_node.h"
#include <string>
#include <iostream>

namespace cypher::tree {
    class label_node : public ast_node {
    public:
        label_node(const std::string& label): _label{label} 
        {
            _type = ast_node_types::LABEL;
        }
        void print() const override {
            std::cout << "label value: " << _label;
        }

    private:
        std::string _label;
    };
};
#endif

