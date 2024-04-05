#include <FlexLexer.h>

#include "astdriver.hpp"

int yyFlexLexer::yywrap() 
{
    return 1;
}

int main(void)
{
    FlexLexer *lexer = new yyFlexLexer;
    lexer->set_debug(1);
    yy::AstDriver driver{lexer};
    driver.parse();
    delete lexer;
    return 0;
}
