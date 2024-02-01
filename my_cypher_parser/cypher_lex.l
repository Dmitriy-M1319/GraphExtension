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
{DIGIT1}{DIGIT}*        { cout << "number (" << yytext << ")" << endl; return 1; }
\"{LABEL}\"             { cout << "string in quotes (" << yytext << ")" << endl; return 1; }
{OBJ_NAME}              { cout << "object name (" << yytext << ")" << endl; return 1; }
{LABEL}                 { cout << "label (" << yytext << ")" << endl; return 1; }
{COMMAND}               { cout << "language command (" << yytext << ")" << endl; return 1; }
.                       { cout << "UNKNOWN" << endl; return 1; }       

%%
