#ifndef STMT_NODES_H
#define STMT_NODES_H

#include "ast_node.h"
#include "object_name_node.h"
#include "base_nodes.h"
#include "edge_nodes.h"
#include <optional>
#include <string>
namespace cypher::tree {
    
    class assign_node : public ast_node {
    public:
        assign_node(const object_name_node& name, const std::string& value):
            _name{name}, _value{value} 
        {
            _childs.push_back(_name);
            _type = ast_node_types::ASSIGN;    
        }

        void print() override {
            std::cout << "Assign: " << std::endl;
            _name.print();
            std::cout << " = " << _value << std::endl;
        }
    private:
        object_name_node _name;
        std::string _value;
    };

    class object_list_node : public ast_node {
    public:
        object_list_node(const std::vector<object_name_node>& list, ast_node *parent) {
            _parent = parent;
            _type = ast_node_types::OBJECT_LIST;
            std::copy(list.begin(), list.end(), _childs.begin());
        }

        void print() override {
            std::cout << "Object names list:" << std::endl;
            for (auto& p : _childs) {
                p.print();
                std::cout << std::endl;
            }
        }
    };

    class return_stmt_node : public chstate_stmt {
    public:
        return_stmt_node(const object_list_node& list, ast_node *parent): _objects(list) {
            _parent = parent;
            _type = ast_node_types::RETURN_STMT;
        }

        void print() override {
            std::cout << "Return statement:" << std::endl;
            _objects.print();
        }
    private:
        object_list_node _objects;
    };

    class set_stmt_node : public chstate_stmt {
    public:
        set_stmt_node(const assign_node& assnina, ast_node *parent): _ass(assnina) {
            _parent = parent;
            _type = ast_node_types::SET_STMT;
        }

        void print() override {
            std::cout << "Set statement:" << std::endl;
            _ass.print();
        }
    private:
        assign_node _ass;
    };

    class delete_stmt_node : public chstate_stmt {
    public:
        delete_stmt_node(const object_name_node& name, ast_node *parent): _name(name) {
            _parent = parent;
            _type = ast_node_types::DELETE_STMT;
        }

        void print() override {
            std::cout << "Delete statement:" << std::endl;
            _name.print();
        }
    private:
        object_name_node _name;
    };

    class where_stmt_node : public ast_node {
    public:
        where_stmt_node(const assign_node& assnina, ast_node *parent): _ass(assnina) {
            _parent = parent;
            _type = ast_node_types::WHERE_STMT;
        }

        void print() override {
            std::cout << "Where statement:" << std::endl;
            _ass.print();
        }
    private:
        assign_node _ass;
    };
    
    class edge_assign_node : public match_body_node {
    public:
        edge_assign_node(const edges_list& lst, 
                std::optional<object_name_node> name, ast_node *parent): _lst(lst), _name(name) {
            _parent = parent;
            _type = ast_node_types::EDGE_ASSIGN;
        }

        void print() override {
            std::cout << "Assign statement:" << std::endl;
            if(_name.has_value()) {
                _name->print();
                std::cout << " = " << std::endl;
            }
            _lst.print();
        }
    private:
        edges_list _lst;
        std::optional<object_name_node> _name;
    };

    
    class match_stmt_node : public stmt_node {
    public:
        match_stmt_node(const object_name_node& name,
            match_body_node* body,
            std::optional<where_stmt_node> where_stmt,
            chstate_stmt *chstmt,
            ast_node *parent): _name(name), _body(body), _where(where_stmt), _chstmt(chstmt) {
            _parent = parent;
            _type = ast_node_types::MATCH_STMT;
        }

        void print() override {
            std::cout << "MATCH statement:" << std::endl;
            _name.print();
            _body->print();
            if(_where.has_value()) {
                _where->print();
            }
            _chstmt->print();
        }
    private:
        object_name_node _name;
        match_body_node* _body;
        std::optional<where_stmt_node> _where;
        chstate_stmt *_chstmt;
    };


};

#endif
