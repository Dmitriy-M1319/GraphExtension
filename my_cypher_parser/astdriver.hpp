#ifndef AST_DRIVER_H
#define AST_DRIVER_H

#include "astgrammar.tab.hh"
#include <FlexLexer.h>

namespace yy {

class AstDriver {

public:
    AstDriver(FlexLexer *plex) : plex_(plex) {}

    parser::token_type yylex(parser::semantic_type *yylval) {
        parser::token_type tt = static_cast<parser::token_type>(plex_->yylex());
        if (tt == yy::parser::token_type::NUMBER)
            yylval->as<int>() = std::stoi(plex_->YYText());
        return tt;
    }

    bool parse() {
        parser parser(this);
        bool res = parser.parse();
        return !res;
    }

private:
    FlexLexer *plex_;
};

}

#endif
