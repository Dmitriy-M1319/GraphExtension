%option c++

%{

#include "cypher.tab.hh"

%}

WS          [ |\t|\n|\v]+
DIGIT       [0-9]+
DIGIT1      [1-9]+
COMMAND     [A-Z]+
OBJ_NAME    [a-z]+
LABEL       [a-zA-Z]+

%%

{WS}                    /* skip */
CREATE                  { return yy::parser::token_type::CREATE; }
MATCH                   { return yy::parser::token_type::MATCH; }
FROM                    { return yy::parser::token_type::FROM; }
WHERE                   { return yy::parser::token_type::WHERE; }
RETURN                  { return yy::parser::token_type::RETURN; }
SET                     { return yy::parser::token_type::SET; }
DELETE                  { return yy::parser::token_type::DELETE; }
GRAPH                   { return yy::parser::token_type::GRAPH; }
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
{DIGIT1}{DIGIT}*        { return yy::parser::token_type::NUMBER; }
\"{LABEL}\"             { return yy::parser::token_type::STR_VALUE; }
{OBJ_NAME}              { return yy::parser::token_type::OBJ_NAME; }
{LABEL}                 { return yy::parser::token_type::LABEL; }
.                       { return yy::parser::token_type::UNKNOWN; }       

%%
