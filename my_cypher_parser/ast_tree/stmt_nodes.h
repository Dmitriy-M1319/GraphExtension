#ifndef STMT_NODES_H
#define STMT_NODES_H

#include "ast_node.h"
#include "object_name_node.h"
#include "base_nodes.h"
#include "edge_nodes.h"
#include <memory>
#include <optional>
#include <string>

namespace cypher::tree {
    
    class assign_node : public ast_node {
    public:
        assign_node(object_name_node *name, const std::string& prop, const std::string& value):
            _name{name}, _prop{prop}, _value{value} 
        {
            _childs.push_back(_name);
            _type = ast_node_types::ASSIGN;    
        }

        void print() const override {
            std::cout << "Assign: " << std::endl;
            _name->print();
            std::cout << " = " << _value << std::endl;
        }
    private:
        object_name_node *_name;
        std::string _value;
        std::string _prop;
    };

    class object_list_node : public ast_node {
    public:
        object_list_node(const std::vector<object_name_node *>& list) {
            _type = ast_node_types::OBJECT_LIST;
            std::copy(list.begin(), list.end(), _childs.begin());
        }

        void print() const override {
            std::cout << "Object names list:" << std::endl;
            for (const auto p : _childs) {
                p->print();
                std::cout << std::endl;
            }
        }
    };

    class return_stmt_node : public chstate_stmt {
    public:
        return_stmt_node(object_list_node *list): _objects(list) {
            _type = ast_node_types::RETURN_STMT;
            _childs.push_back(list);
        }

        void print() const override {
            std::cout << "Return statement:" << std::endl;
            _objects->print();
        }
    private:
        object_list_node *_objects;
    };

    class set_stmt_node : public chstate_stmt {
    public:
        set_stmt_node(assign_node *assnina): _ass(assnina) {
            _type = ast_node_types::SET_STMT;
            _childs.push_back(assnina);
        }

        void print() const override {
            std::cout << "Set statement:" << std::endl;
            _ass->print();
        }
    private:
        assign_node *_ass;
    };

    class delete_stmt_node : public chstate_stmt {
    public:
        delete_stmt_node(object_name_node *name): _name(name) {
            _type = ast_node_types::DELETE_STMT;
            _childs.push_back(name);
        }

        void print() const override {
            std::cout << "Delete statement:" << std::endl;
            _name->print();
        }
    private:
        object_name_node *_name;
    };

    class where_stmt_node : public ast_node {
    public:
        where_stmt_node(assign_node *assnina): _ass(assnina) {
            _type = ast_node_types::WHERE_STMT;
            _childs.push_back(assnina);
        }

        void print() const override {
            std::cout << "Where statement:" << std::endl;
            _ass->print();
        }
    private:
        assign_node *_ass;
    };
    
    class edge_assign_node : public match_body_node {
    public:
        edge_assign_node(edges_list *lst, 
                std::optional<object_name_node *> name): _lst(lst), _name(name) {
            _type = ast_node_types::EDGE_ASSIGN;
            _childs.push_back(lst);
            if(name) {
                _childs.push_back(name.value());
            }
        }

        void print() const override {
            std::cout << "Assign statement:" << std::endl;
            if(_name.has_value()) {
                _name.value()->print();
                std::cout << " = " << std::endl;
            }
            _lst->print();
        }
    private:
        edges_list *_lst;
        std::optional<object_name_node *> _name;
    };

    
    class match_stmt_node : public stmt_node {
    public:
        match_stmt_node(object_name_node *name,
            match_body_node* body,
            std::optional<where_stmt_node *> where_stmt,
            chstate_stmt *chstmt): _name(name), _body_ptr(std::move(body)), _where(where_stmt), _chstmt_ptr(std::move(chstmt)) {
            _type = ast_node_types::MATCH_STMT;
            _childs.push_back(name);
            _childs.push_back(body);
            if(where_stmt) {
                _childs.push_back(where_stmt.value());
            }
            _childs.push_back(chstmt);
        }

        void print() const override {
            std::cout << "MATCH statement:" << std::endl;
            _name->print();
            _body_ptr->print();
            if(_where.has_value()) {
                _where.value()->print();
            }
            _chstmt_ptr->print();
        }
    private:
        object_name_node *_name;
        match_body_node *_body_ptr;
        std::optional<where_stmt_node *> _where;
        chstate_stmt *_chstmt_ptr;
    };

    class create_stmt_node : public stmt_node {
    public:
        create_stmt_node(object_name_node *name,
            vertices_list_node *list,
            std::optional<edges_list *> edges) : _name(name), _list(list), _edges(edges) {
            _type = ast_node_types::CREATE_STMT;
            _childs.push_back(name);
            _childs.push_back(list);
            if(edges) {
                _childs.push_back(edges.value());
            }
        }
        void print() const override {
            std::cout << "CREATE statement:" << std::endl;
            _name->print();
            _list->print();
            if(_edges.has_value()) {
                _edges.value()->print();
            }
        }
    private:
        object_name_node *_name;
        vertices_list_node *_list;
        std::optional<std::shared_ptr<edges_list>> _edges;
    };

};

#endif
