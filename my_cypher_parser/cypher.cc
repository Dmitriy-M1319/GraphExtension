#include <FlexLexer.h>
#include <cstdio>

#include "astdriver.hpp"

int yyFlexLexer::yywrap() 
{
    return 1;
}

int main(void)
{
    FlexLexer *lexer = new yyFlexLexer;
    //lexer->set_debug(1);
    yy::AstDriver driver{lexer};
    driver.parse();
    driver.print_tree();
    delete lexer;
    return 0;
}
