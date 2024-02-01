#include <FlexLexer.h>

int yyFlexLexer::yywrap() 
{
    return 1;
}

int main(void)
{
    FlexLexer *lexer = new yyFlexLexer;
    while(lexer->yylex() != 0) {
        // do nothing
    }

    delete lexer;
    return 0;
}
