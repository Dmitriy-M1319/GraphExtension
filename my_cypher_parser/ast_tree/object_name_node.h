#ifndef OBJECT_NAME_NODE_H
#define OBJECT_NAME_NODE_H

#include "ast_node.h"
#include <iostream>
#include <string>

namespace cypher::tree {
    class object_name_node : public ast_node {
    public:
        object_name_node(const std::string& name): _name{name} 
        {
            _type = ast_node_types::OBJECT_NAME;
        }
        void print(int tabs) const override {
            for(int i = 0; i < tabs; ++i)
                std::cout << " ";
            std::cout <<  "-- object value: " << _name << std::endl;
        }

    private:
        std::string _name;
    };
};
#endif
