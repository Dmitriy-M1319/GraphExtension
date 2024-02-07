#ifndef BASE_NODES_H
#define BASE_NODES_H

#include "ast_node.h"

namespace cypher::tree {
    class chstate_stmt : public ast_node {};
    class match_body_node : public ast_node {};
    class stmt_node : public ast_node {};
};

#endif
