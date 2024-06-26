%option c++

%{

#include "astgrammar.tab.hh"
#include <iostream>

#define print(value, type) std::cout << "Value: " << value << ", Type: " << type << std::endl

%}

WS          [ |\t|\n|\v]+
COMMAND     [A-Z]+
OBJ_NAME    [a-z0-9_]+
LABEL       [a-zA-Z0-9]+

%%

{WS}                    /* skip */
CREATE                  { return yy::parser::token_type::CREATE; }
MATCH                   { return yy::parser::token_type::MATCH; }
FROM                    { return yy::parser::token_type::FROMKEYWORD; }
WHERE                   { return yy::parser::token_type::WHERE; }
RETURN                  { return yy::parser::token_type::RETURN; }
SET                     { return yy::parser::token_type::SET; }
DELETE                  { return yy::parser::token_type::DELETE; }
GRAPH                   { return yy::parser::token_type::GRAPH; }
"$"                     { return yy::parser::token_type::EMPTY; }
"="                     { return yy::parser::token_type::ASSIGN; }
"("                     { return yy::parser::token_type::LBRACE; }
")"                     { return yy::parser::token_type::RBRACE; }
"{"                     { return yy::parser::token_type::LPAREN; }
"}"                     { return yy::parser::token_type::RPAREN; }
"["                     { return yy::parser::token_type::LBRACKET; }
"]"                     { return yy::parser::token_type::RBRACKET; }
":"                     { return yy::parser::token_type::COLON; }
";"                     { return yy::parser::token_type::SEMICOLON; }
"->"                    { return yy::parser::token_type::TO; }
"-"                     { return yy::parser::token_type::FROM; }
","                     { return yy::parser::token_type::COMMA; }
"."                     { return yy::parser::token_type::POINT; }
[-+]?[0-9]+             { return yy::parser::token_type::NUMBER; }
\"{LABEL}\"             { return yy::parser::token_type::STR_VALUE; }
{OBJ_NAME}              { return yy::parser::token_type::OBJECT_NAME; }
{LABEL}                 { return yy::parser::token_type::LABEL_TYPE; }
.                       { return yy::parser::token_type::UNKNOWN; }

%%
