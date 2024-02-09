#ifndef AST_NODE_H
#define AST_NODE_H

#include "types.h"
#include <vector>

namespace cypher::tree {
// Базовый класс узла синтаксического дерева
    class ast_node {
    public:
        // Пока что так, позже перегрузим оператор <<
        virtual void print() const = 0;

        const std::vector<ast_node*>& get_childs() const {
            return _childs;
        }

        virtual ~ast_node(){};
    protected:
        std::vector<ast_node *> _childs;
        ast_node_types _type;
    };
};
#endif
