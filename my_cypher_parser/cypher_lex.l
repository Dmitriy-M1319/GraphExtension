%option c++

%{

#include <iostream>

using std::cout;
using std::endl;

%}

WS          [ |\t|\n|\v]+
DIGIT       [0-9]+
DIGIT1      [1-9]+
COMMAND     [A-Z]+
OBJ_NAME    [a-z]+
LABEL   [a-zA-Z]+

%%

{WS}                    /* skip */
","                     /* skip */
CREATE                  { cout << "CREATE" << endl; return 1; }
MATCH                   { cout << "MATCH" << endl; return 1; }
FROM                    { cout << "FROM" << endl; return 1; }
WHERE                   { cout << "WHERE" << endl; return 1; }
RETURN                  { cout << "RETURN" << endl; return 1; }
SET                     { cout << "SET" << endl; return 1; }
DELETE                  { cout << "DELETE" << endl; return 1; }
GRAPH                   { cout << "DELETE" << endl; return 1; }
"="                     { cout << "is" << endl; return 1; }
"("                     { cout << "left bracket(" << endl; return 1; }
")"                     { cout << "right bracket)" << endl; return 1; }
"{"                     { cout << "left brace{" << endl; return 1; }
"}"                     { cout << "right brace}" << endl; return 1; }
"["                     { cout << "left bracket[" << endl; return 1; }
"]"                     { cout << "right bracket]" << endl; return 1; }
":"                     { cout << "colon" << endl; return 1; }
";"                     { cout << "semicolon" << endl; return 1; }
"->"                    { cout << "to" << endl; return 1; }
"-"                     { cout << "from" << endl; return 1; }
","                     { cout << "comma" << endl; return 1; }
"."                     { cout << "point" << endl; return 1; }
{DIGIT1}{DIGIT}*        { cout << "number (" << yytext << ")" << endl; return 1; }
\"{LABEL}\"             { cout << "string in quotes (" << yytext << ")" << endl; return 1; }
{OBJ_NAME}              { cout << "object name (" << yytext << ")" << endl; return 1; }
{LABEL}                 { cout << "label (" << yytext << ")" << endl; return 1; }
.                       { cout << "UNKNOWN" << endl; return 1; }       

%%
