#ifndef STMT_NODES_H
#define STMT_NODES_H

#include "ast_node.h"
#include "object_name_node.h"
#include "edge_nodes.h"
#include "vertices_list.h"
#include <iterator>
#include <memory>
#include <optional>
#include <string>
#include <variant>

namespace cypher::tree {
    
    class assign_node : public ast_node {
    public:
        using name_opt = std::optional<std::shared_ptr<object_name_node>>;
        assign_node(name_opt&& name, std::string&& prop, std::string&& value):
            _name{std::move(name)}, _prop{std::move(prop)}, _value{std::move(value)} 
        {
            _type = ast_node_types::ASSIGN;    
        }

        assign_node(name_opt&& name, std::string&& prop, int value):
            _name{std::move(name)}, _prop{std::move(prop)}, _value{value} 
        {
            std::cout << "int ctor" << std::endl;
            _type = ast_node_types::ASSIGN;    
        }
        void print(int tabs) const override {
            for(int i = 0; i < tabs; ++i)
                std::cout << " ";
            std::cout << "-- assign:" << std::endl;
            _name.value()->print(tabs + 2);

            for(int i = 0; i < tabs; ++i)
                std::cout << " ";
            if(std::holds_alternative<int>(_value))
                std::cout << " = " << std::get<int>(_value) << std::endl;
            else
                std::cout << " = " << std::get<std::string>(_value) << std::endl;
        }
    private:
        name_opt _name;
        std::variant<std::string, int> _value;
        std::string _prop;
    };

    class object_list_node : public ast_node {
    public:
        object_list_node(const std::vector<std::shared_ptr<object_name_node>>& list) {
            std::move(list.begin(), list.end(), std::back_inserter(_nodes));
        }

        void append(std::shared_ptr<object_list_node>&& node) {
            std::move(node->_nodes.begin(), node->_nodes.end(), std::back_inserter(_nodes));
        }

        void append(std::shared_ptr<object_name_node>&& node) {
            _nodes.emplace_back(std::move(node));
        }

        object_list_node(std::shared_ptr<object_list_node>&& node) {
            this->append(std::move(node));
        }

        void print(int tabs) const override {
            for(int i = 0; i < tabs; ++i)
                std::cout << " ";
            std::cout << "-- object list:" << std::endl;
            for (const auto p : _nodes) {
                p->print(tabs + 2);
            }
        }
    private:
        std::vector<std::shared_ptr<object_name_node>> _nodes;
    };


    class return_stmt_node : public ast_node {
    public:
        using names_list_opt = std::optional<std::shared_ptr<object_list_node>>;
        return_stmt_node(names_list_opt&& list): _objects(std::move(list)) {
            _type = ast_node_types::RETURN_STMT;
        }

        void print(int tabs) const override {
            for(int i = 0; i < tabs; ++i)
                std::cout << " ";
            std::cout << "-- return statement:" << std::endl;
            _objects.value()->print(tabs + 2);
        }
    private:
        names_list_opt _objects;
    };


    class set_stmt_node : public ast_node {
    public:
        using ass_opt = std::optional<std::shared_ptr<assign_node>>;
        set_stmt_node(ass_opt&& assnina): _ass(std::move(assnina)) {
            _type = ast_node_types::SET_STMT;
        }

        void print(int tabs) const override {
            for(int i = 0; i < tabs; ++i)
                std::cout << " ";
            std::cout << "-- set statement:" << std::endl;
            _ass.value()->print(tabs + 2);
        }
    private:
        ass_opt _ass;
    };


    class delete_stmt_node : public ast_node {
    public:
        using name_opt = std::optional<std::shared_ptr<object_name_node>>;
        delete_stmt_node(name_opt&& name): _name(std::move(name)) {
            _type = ast_node_types::DELETE_STMT;
        }

        void print(int tabs) const override {
            for(int i = 0; i < tabs; ++i)
                std::cout << " ";
            std::cout << "-- delete statement:" << std::endl;
            _name.value()->print(tabs + 2);
        }
    private:
        name_opt _name;
    };


    class chstate_stmt : public ast_node {
    public:
       chstate_stmt(std::shared_ptr<set_stmt_node>&& node): _stmt{std::move(node)} {}
       chstate_stmt(std::shared_ptr<delete_stmt_node>&& node): _stmt{std::move(node)} {}
       chstate_stmt(std::shared_ptr<return_stmt_node>&& node): _stmt{std::move(node)} {}

       void print(int tabs) const override {
            for(int i = 0; i < tabs; ++i)
                std::cout << " ";
           std::cout << " -- change statement:" << std::endl;
           if(std::holds_alternative<std::shared_ptr<set_stmt_node>>(_stmt))
                std::get<std::shared_ptr<set_stmt_node>>(_stmt)->print(tabs + 2);
           else if(std::holds_alternative<std::shared_ptr<delete_stmt_node>>(_stmt))
                std::get<std::shared_ptr<delete_stmt_node>>(_stmt)->print(tabs + 2);
           else
                std::get<std::shared_ptr<return_stmt_node>>(_stmt)->print(tabs + 2);
       }

    private:
        std::variant<std::shared_ptr<set_stmt_node>, 
            std::shared_ptr<delete_stmt_node>, 
            std::shared_ptr<return_stmt_node>> _stmt;
    };


    class where_stmt_node : public ast_node {
    public:
        using ass_opt = std::optional<std::shared_ptr<assign_node>>;
        where_stmt_node() : ast_node(), _ass{std::nullopt} {}
        where_stmt_node(ass_opt&& assnina): _ass(std::move(assnina)) {
            _type = ast_node_types::WHERE_STMT;
        }

        void print(int tabs) const override {
            if(_ass.has_value()) {
                for(int i = 0; i < tabs; ++i)
                    std::cout << " ";
                std::cout << "-- where statement:" << std::endl;
                _ass.value()->print(tabs);
            }
        }
    private:
        ass_opt _ass;
    };

    
    class edge_assign_node : public ast_node {
    public:
        using edges_opt = std::optional<std::shared_ptr<edges_list_node>>;
        using name_opt = std::optional<std::shared_ptr<object_name_node>>;

        edge_assign_node(edges_opt&& lst, 
                name_opt&& name): _lst(std::move(lst)), _name(std::move(name)) {
            _type = ast_node_types::EDGE_ASSIGN;
        }

        void print(int tabs) const override {
            for(int i = 0; i < tabs; ++i)
                std::cout << " ";
            std::cout << "-- edge assign statement:" << std::endl;
            if(_name.has_value()) {
                _name.value()->print(tabs + 2);
                std::cout << "| to" << std::endl;
            }
            _lst.value()->print(tabs + 2);
        }
    private:
        edges_opt _lst;
        name_opt _name;
    };

    class match_body_node : public ast_node {
    public:
       match_body_node(std::shared_ptr<edge_assign_node>&& node): _stmt{std::move(node)} {}
       match_body_node(std::shared_ptr<vertices_list_node>&& node): _stmt{std::move(node)} {}

       void print(int tabs) const override {
            for(int i = 0; i < tabs; ++i)
                std::cout << " ";
           std::cout << "-- match query body:" << std::endl;
           if(std::holds_alternative<std::shared_ptr<edge_assign_node>>(_stmt))
               std::get<std::shared_ptr<edge_assign_node>>(_stmt)->print(tabs + 2);
           else
               std::get<std::shared_ptr<vertices_list_node>>(_stmt)->print(tabs + 2);
       }

    private:
        std::variant<std::shared_ptr<edge_assign_node>, 
            std::shared_ptr<vertices_list_node>> _stmt;
    };
    
    class match_stmt_node : public ast_node {
    public:
        using body_opt = std::optional<std::shared_ptr<match_body_node>>;
        using where_opt = std::optional<std::shared_ptr<where_stmt_node>>;
        using name_opt = std::optional<std::shared_ptr<object_name_node>>;
        using chstate_opt = std::optional<std::shared_ptr<chstate_stmt>>;

        match_stmt_node(name_opt&& name, body_opt&& body, where_opt&& where_stmt,
            chstate_opt&& chstmt): _name(name), _body_ptr(std::move(body)), _where(where_stmt), _chstmt_ptr(std::move(chstmt)) {
            _type = ast_node_types::MATCH_STMT;
        }

        void print(int tabs) const override {
            for(int i = 0; i < tabs; ++i)
                std::cout << " ";
            std::cout << "MATCH query:" << std::endl;
            _name.value()->print(tabs + 2);
            _body_ptr.value()->print(tabs + 2);
            if(_where.has_value()) {
                _where.value()->print(tabs + 2);
            }
            _chstmt_ptr.value()->print(tabs + 2);
        }
    private:
        name_opt _name;
        body_opt _body_ptr;
        where_opt _where;
        chstate_opt _chstmt_ptr;
    };

    class create_stmt_node : public ast_node {
    public:
        using vertices_opt = std::optional<std::shared_ptr<vertices_list_node>>;
        using name_opt = std::optional<std::shared_ptr<object_name_node>>;
        using edges_opt = std::optional<std::shared_ptr<edges_list_node>>;

        create_stmt_node(name_opt&& name, vertices_opt&& list, edges_opt&& edges): 
            _name(std::move(name)), _list(std::move(list)), _edges(std::move(edges))
        {
            _type = ast_node_types::CREATE_STMT;
        }
        void print(int tabs) const override {
            for(int i = 0; i < tabs; ++i)
                std::cout << " ";
            std::cout << "CREATE query:" << std::endl;
            if(_name.has_value())
                _name.value()->print(tabs + 2);
            if(_list.has_value())
                _list.value()->print(tabs + 2);
            if(_edges.has_value()) {
                _edges.value()->print(tabs + 2);
            }
        }
    private:
        name_opt _name;
        vertices_opt _list;
        edges_opt _edges;
    };

};

#endif
