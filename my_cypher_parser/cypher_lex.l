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
CREATE                  { print(yytext, "CREATE"); return yy::parser::token_type::CREATE; }
MATCH                   { print(yytext, "MATCH"); return yy::parser::token_type::MATCH; }
FROM                    { print(yytext, "FROMKEYWORD"); return yy::parser::token_type::FROMKEYWORD; }
WHERE                   { print(yytext, "WHERE"); return yy::parser::token_type::WHERE; }
RETURN                  { print(yytext, "RETURN"); return yy::parser::token_type::RETURN; }
SET                     { print(yytext, "SET"); return yy::parser::token_type::SET; }
DELETE                  { print(yytext, "DELETE"); return yy::parser::token_type::DELETE; }
GRAPH                   { print(yytext, "GRAPH"); return yy::parser::token_type::GRAPH; }
"$"                     { print(yytext, "EMPTY"); return yy::parser::token_type::EMPTY; }
"="                     { print(yytext, "ASSIGN"); return yy::parser::token_type::ASSIGN; }
"("                     { print(yytext, "LBRACE"); return yy::parser::token_type::LBRACE; }
")"                     { print(yytext, "RBRACE"); return yy::parser::token_type::RBRACE; }
"{"                     { print(yytext, "LPAREN"); return yy::parser::token_type::LPAREN; }
"}"                     { print(yytext, "RPAREN"); return yy::parser::token_type::RPAREN; }
"["                     { print(yytext, "LBRACKET"); return yy::parser::token_type::LBRACKET; }
"]"                     { print(yytext, "RBRACKET"); return yy::parser::token_type::RBRACKET; }
":"                     { print(yytext, "COLON"); return yy::parser::token_type::COLON; }
";"                     { print(yytext, "SEMICOLON"); return yy::parser::token_type::SEMICOLON; }
"->"                    { print(yytext, "TO"); return yy::parser::token_type::TO; }
"-"                     { print(yytext, "FROM"); return yy::parser::token_type::FROM; }
","                     { print(yytext, "COMMA"); return yy::parser::token_type::COMMA; }
"."                     { print(yytext, "POINT"); return yy::parser::token_type::POINT; }
[-+]?[0-9]+             { print(yytext, "NUMBER"); return yy::parser::token_type::NUMBER; }
\"{LABEL}\"             { print(yytext, "STR_VALUE"); return yy::parser::token_type::STR_VALUE; }
{OBJ_NAME}              { print(yytext, "OBJECT_NAME"); return yy::parser::token_type::OBJECT_NAME; }
{LABEL}                 { print(yytext, "LABEL_TYPE"); return yy::parser::token_type::LABEL_TYPE; }
.                       { print(yytext, "UNRKOWN"); return yy::parser::token_type::UNKNOWN; }       

%%
