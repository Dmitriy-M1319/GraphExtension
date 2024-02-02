#ifndef KEY_VALUE_NODE_H
#define KEY_VALUE_NODE_H

#include "object_name_node.h"
#include <iostream>

namespace cypher::tree {
    class key_value_node : public ast_node {
    public:
        key_value_node(const object_name_node& obj_node, const std::string& value):
            _key{obj_node}, _value{value} 
        {
            _childs.push_back(_key);
            _type = ast_node_types::KEY_VALUE;    
        }

        void print() override {
            std::cout << "key-value: " << std::endl;
            _key.print();
            std::cout << "Value: " << _value << std::endl;
        }
        
    private:
        object_name_node _key;
        std::string _value;
    };
};
#endif
