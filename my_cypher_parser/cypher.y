%language "c++"

%skeleton "lalr1.cc"
%defines
%define api.value.type variant
%param {yy::AstDriver* driver}

%code requires {

//TODO: Посмотреть примеры реализации разбора списков объектов

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
#include <optional>
#include <vector>

using cypher::tree::object_name_node;
using cypher::tree::key_value_node;
using cypher::tree::label_node;
using cypher::tree::vertex_body_node;
using cypher::tree::vertex_node;
using cypher::tree::vertices_list_node;
using cypher::tree::edge_node;
using cypher::tree::edge_list;
using cypher::tree::assign_node;
using cypher::tree::object_list_node;
using cypher::tree::return_stmt_node;
using cypher::tree::set_stmt_node;
using cypher::tree::delete_stmt_node;
using cypher::tree::chstate_stmt;
using cypher::tree::where_stmt_node;
using cypher::tree::edge_assign_node;
using cypher::tree::match_body;
using cypher::tree::match_body;
using cypher::tree::match_stmt_node;
using cypher::tree::create_stmt_node;
using cypher::tree::stmt_node;

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

%nterm <std::shared_ptr<object_name_node>> obj_name
%nterm <std::shared_ptr<key_value_node>> key_value
%nterm <std::shared_ptr<label_node>> label
%nterm <std::shared_ptr<vertex_body_node>> vertex_body
%nterm <std::shared_ptr<vertex_node>> vertex
%nterm <std::shared_ptr<vertices_list_node>> vertices_list
%nterm <std::shared_ptr<edge_node>> edge
%nterm <std::shared_ptr<edge_list>> edges_list
%nterm <std::shared_ptr<assign_node>> assign
%nterm <std::shared_ptr<object_list_node>> obj_list
%nterm <std::shared_ptr<return_stmt_node>> return_stmt
%nterm <std::shared_ptr<set_stmt_node>> set_stmt
%nterm <std::shared_ptr<delete_stmt_node>> delete_stmt
%nterm <std::shared_ptr<chstate_stmt>> chstate_stmts
%nterm <std::shared_ptr<where_stmt_node>> where_stmt
%nterm <std::shared_ptr<edge_assign_node>> edge_assign
%nterm <std::shared_ptr<match_body>> match_body
%nterm <std::shared_ptr<match_body>> match_body
%nterm <std::shared_ptr<match_stmt_node>> match_stmt
%nterm <std::shared_ptr<create_stmt_node>> create_stmt
%nterm <std::shared_ptr<stmt_node>> stmt

%start  stmt

%%

stmt: create_stmt {$$ = $1}
    | match_stmt {$$ = $1}
;

create_stmt: CREATE GRAPH obj_name vertices_list COMMA edges_list { $$ = std::make_shared<create_stmt_node>($3, $4, $5); }
           | CREATE GRAPH obj_name vertices_list { $$ = std::make_shared<create_stmt_node>($3, $4, std::nullopt); } 
;

match_stmt: MATCH FROM obj_name match_body where_stmt chstate_stmts { $$ = std::make_shared<match_stmt_node>($3, $4, $5, $6); }
          | MATCH FROM obj_name match_body chstate_stmts  { $$ = std::make_shared<match_stmt_node>($3, $4, std::nullopt, $5); }
;

match_body: egde_assign {$$ = $1}
           | vertices_list {$$ = $1}
;

edge_assign: obj_name ASSIGN edges_list { $$ = std::make_shared<edge_assign_node>($1, $3); }
           | edges_list { $$ = std::make_shared<edge_assign_node>(std::nullopt, $1); }
;

where_stmt: WHERE assign { $$ = std::make_shared<where_stmt_node>($2); }
          | EMPTY {}
;

chstate_stmts: set_stmt {$$ = $1}
             | delete_stmt {$$ = $1}
             | return_stmt {$$ = $1}
;

delete_stmt: DELETE obj_name { $$ = std::make_shared<delete_stmt_node>($2); }
;

set_stmt: SET assign { $$ = std::make_shared<set_stmt_node>($2); }
;

return_stmt: RETURN obj_list { $$ = std::make_shared<return_stmt_node>($2); }
;

obj_list: obj_name COMMA obj_list {}
        | obj_name
;

assign: obj_name POINT OBJ_NAME ASSIGN STR_VALUE { $$ = std::make_shared<assign_node>($1, $3, $5); }
;

edges_list: LBRACE edge COMMA edges_list RBRACE {}
          | LBRACE edge RBRACE {
              std::vector<edge_node *> v {$2};
              $$ = std::make_shared<vertices_list_node>(v);
            }
;

edge: vertices_list FROM LBRACKET obj_name COLON label RBRACKET TO vertices_list { $$ = std::make_shared<edge_node>($4, $6, $1, $9); }
;

vertices_list: LBRACE vertex COMMA vertices_list RBRACE { $$ = std::make_shared<vertices_list_node>($4, $2); }
             | LBRACE vertex RBRACE {
                 std::vector<vertex_node *> v;
                 $$ = std::make_shared<vertices_list_node>(v, $2);
               }
;

vertex: obj_name COLON label LPAREN vertex_body RPAREN { $$ = std::make_shared<vertex_body>($5, $3, $1); }
      | obj_name COLON label {$$ = std::make_shared<vertex_body>(std::nullopt, $3, $1); }
      | EMPTY { /* Пока не понимаю, что надо впихнуть, потом придумаю пустой конструктор */}
;

vertex_body: key_value COMMA vertex_body { $$ = make_shared<vertex_body_node>($3->get_childs(), $1); }
           | key_value { 
              std::vector<vertex_vody*> v;
              $$ = make_shared<vertex_body_node>(v, $1); 
            }
;

label: LABEL { $$ = make_shared<key_value_node>($1); }
     | EMPTY { $$ = make_shared<key_value_node>(""); }
;

key_value: obj_name COLON STR_VALUE { $$ = make_shared<key_value_node>($1, $3); }
;

obj_name: STR_VALUE { $$ = std::make_shared<object_name_node>($1); } 
        | EMPTY { $$ = std::make_shared<object_name_node>(""); }
;

%%

namespace yy {

parser::token_type yylex(parser::semantic_type *yylval, AstDriver *driver) {
    return driver->yylex(yylval);
}

void parser::error(const std::string&){}
}
