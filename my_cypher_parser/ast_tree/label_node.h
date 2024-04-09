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
        void print(int tabs) const override {
            for(int i = 0; i < tabs; ++i)
                std::cout << " ";
            std::cout << "-- label value: " << _label << std::endl;
        }

    private:
        std::string _label;
    };
};
#endif

