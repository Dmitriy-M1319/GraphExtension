#ifndef KEY_VALUE_NODE_H
#define KEY_VALUE_NODE_H

#include "object_name_node.h"
#include <iostream>
#include <variant>
#include <memory>

namespace cypher::tree {
    class key_value_node : public ast_node {
    public:
        key_value_node(std::shared_ptr<object_name_node>&& obj_node, int value):
            _key{std::move(obj_node)}, _value{value} 
        {
            _childs.push_back(_key.get());
            _type = ast_node_types::KEY_VALUE;    
        }

        key_value_node(std::shared_ptr<object_name_node>&& obj_node, std::string value):
            _key{std::move(obj_node)}, _value{value} 
        {
            _childs.push_back(_key.get());
            _type = ast_node_types::KEY_VALUE;    
        }

        void print() const override {
            std::cout << "key-value: " << std::endl;
            _key->print();
            if(std::holds_alternative<int>(_value))
                std::cout << "Value: " << std::get<int>(_value) << std::endl;
            else
                std::cout << "Value: " << std::get<std::string>(_value) << std::endl;
        }
        
    private:
        std::shared_ptr<object_name_node> _key;
        std::variant<int, std::string> _value;
    };
};
#endif
