%language "c++"

%skeleton "lalr1.cc"
%defines
%define api.value.type variant

%code requires {

#include "ast_tree/ast_node.h"
#include "ast_tree/base_nodes.h"
#include "ast_tree/edge_nodes.h"
#include "ast_tree/key_value_node.h"
#include "ast_tree/label_node.h"
#include "ast_tree/object_name_node.h"
#include "ast_tree/stmt_nodes.h"
#include "ast_tree/types.h"
#include "ast_tree/vertex_body_node.h"
#include "ast_tree/vertex_node.h"
#include "ast_tree/vertices_list.h"

#include <iostream>
#include <string>
#include <memory>

namespace yy { class AstDriver; }
}

%code {

#include "cypher.hpp"

namespace yy {
    parser::token_typeyylex(parser::semantic_type* yylval,                         
                         AstDriver* driver);
}
}

%token CREATE
MATCH
FROM
WHERE
RETURN
SET
DELETE
GRAPH
ASSIGN      "="
LBRACE      "("
RBRACE      ")"
LPAREN      "{"
RPAREN      "}"
LBRACKET    "["
RBRACKET    "]"
COLON       ":"
SEMICOLON   ";"
TO          "->"
FROM        "-"
COMMA       ","
POINT       "."
EMPTY       ""
UNKNOWN
;

%token <int> NUMBER
%token <std::string> STR_VALUE
%token <std::string> OBJECT_NAME
%token <std::string> LABEL_TYPE

%nterm <std::shared_ptr<cypher::tree::object_name_node>> obj_name
%nterm <std::shared_ptr<cypher::tree::key_value_node>> key_value
%nterm <std::shared_ptr<cypher::tree::label_node>> label
%nterm <std::shared_ptr<cypher::tree::vertex_body_node>> vertex_body
%nterm <std::shared_ptr<cypher::tree::vertex_node>> vertex
%nterm <std::shared_ptr<cypher::tree::vertices_list_node>> vertices_list
%nterm <std::shared_ptr<cypher::tree::edge_node>> edge
%nterm <std::shared_ptr<cypher::tree::edge_list>> edges_list
%nterm <std::shared_ptr<cypher::tree::assign_node>> assign
%nterm <std::shared_ptr<cypher::tree::object_list_node>> obj_list
%nterm <std::shared_ptr<cypher::tree::return_stmt_node>> return_stmt
%nterm <std::shared_ptr<cypher::tree::set_stmt_node>> set_stmt
%nterm <std::shared_ptr<cypher::tree::delete_stmt_node>> delete_stmt
%nterm <std::shared_ptr<cypher::tree::chstate_stmt>> chstate_stmts
%nterm <std::shared_ptr<cypher::tree::where_stmt_node>> where_stmt
%nterm <std::shared_ptr<cypher::tree::edge_assign_node>> edge_assign
%nterm <std::shared_ptr<cypher::tree::match_body>> match_body
%nterm <std::shared_ptr<cypher::tree::match_body>> match_body
%nterm <std::shared_ptr<cypher::tree::match_stmt_node>> match_stmt
%nterm <std::shared_ptr<cypher::tree::create_stmt_node>> create_stmt
%nterm <std::shared_ptr<cypher::tree::stmt_node>> stmt

%start  stmt

%%

stmt:   create_stmt                                                                 {}
    |   match_stmt                                                                  {}
;

create_stmt: CREATE GRAPH obj_name vertices_list COMMA edges_list                   {}
;

match_stmt: MATCH FROM obj_name match_body where_stmt chstate_stmts                 {}
;

match_body: egde_assign                                                             {}
           | vertices_list                                                          {}
;

edge_assign: obj_name ASSIGN edges_list                                             {}
           | edges_list                                                             {}
;

where_stmt: WHERE assign                                                            {}
          | EMPTY                                                                   {}
;

chstate_stmts: set_stmt                                                             {}
             | delete_stmt                                                          {}
             | return_stmt                                                          {}
;

delete_stmt: DELETE obj_name                                                        {}
;

set_stmt: SET assign                                                                {}
;

return_stmt: RETURN obj_list                                                        {}
;

obj_list: obj_name COMMA obj_list                                                   {}
        | obj_name
;

assign: obj_name POINT obj_name ASSIGN str_value                                    {}
;

edges_list: LBRACE edge COMMA edges_list RBRACE                                     {}
          | LBRACE edge RBRACE                                                      {}
;

edge: vertices_list FROM LBRACKET obj_name COLON label RBRACKET TO vertices_list    {}
;

vertices_list: LBRACE node COMMA vertices_list RBRACE                               {}
             | LBRACE node RBRACE                                                   {}
;

vertex: obj_name COLON label LPAREN vertex_body RPAREN                              {}
      | obj_name COLON label                                                        {}
      | EMPTY
;

vertex_body: key_value COMMA vertex_body                                            {}
           | key_value                                                              {}
;

label: label                                                                        {}
     | EMPTY                                                                        {}
;

key_value: obj_name COLON str_value                                                 {}
;

obj_name: obj_name | EMPTY                                                          {}
;

%%
