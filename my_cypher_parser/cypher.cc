#include <FlexLexer.h>

#include "astdriver.hpp"

int yyFlexLexer::yywrap() 
{
    return 1;
}

int main(void)
{
    FlexLexer *lexer = new yyFlexLexer;
    yy::AstDriver driver{lexer};
    driver.parse(); 
    delete lexer;
    return 0;
}
