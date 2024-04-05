#ifndef AST_DRIVER_H
#define AST_DRIVER_H

#include <iostream>
#include <memory>
#include <string>

#include "astgrammar.tab.hh"
#include "ast_tree/ast_node.h"
#include <FlexLexer.h>

namespace yy {

class AstDriver {

public:
    AstDriver(FlexLexer *plex) : plex_(plex) {}

    parser::token_type yylex(parser::semantic_type *yylval) {
        parser::token_type tt = static_cast<parser::token_type>(plex_->yylex());
        if (tt == yy::parser::token_type::NUMBER)
            yylval->as<int>() = std::stoi(plex_->YYText());
        if (tt == yy::parser::token_type::STR_VALUE ||
                tt == yy::parser::token_type::OBJECT_NAME ||
                tt == yy::parser::token_type::LABEL_TYPE)
            yylval->as<std::string>() = std::string(plex_->YYText());
        return tt;
    }

    void create_tree(std::shared_ptr<cypher::tree::ast_node> &&tree) {
        tree_ = std::move(tree);
    }

    void print_tree() const {
        tree_->print();
    }

    bool parse() {
        parser parser(this);
        bool res = parser.parse();
        return !res;
    }

private:
    FlexLexer *plex_;
    std::shared_ptr<cypher::tree::ast_node> tree_;
};

}

#endif
