#ifndef AST_NODE_H
#define AST_NODE_H

#include "types.h"
#include <vector>

namespace cypher::tree {
    class ast_node {
    public:
        ast_node(): _childs({}), _type{ast_node_types::EMPTY} {}

        virtual void print() const = 0;

        const std::vector<ast_node*>& get_childs() const {
            return _childs;
        }

        void add_child(ast_node *node) {
            _childs.push_back(node);
        }

        virtual ~ast_node(){};
    protected:
        std::vector<ast_node *> _childs;
        ast_node_types _type;
    };
};
#endif
