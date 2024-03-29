#ifndef TYPES_H
#define TYPES_H

namespace cypher::tree {
    enum class ast_node_types {
        EMPTY,
        OBJECT_NAME,
        LABEL,
        KEY_VALUE,
        VERTEX_BODY,
        VERTEX,
        VERTICES_LIST,
        EDGE,
        EDGES_LIST,
        ASSIGN,
        OBJECT_LIST,
        RETURN_STMT,
        SET_STMT,
        DELETE_STMT,
        WHERE_STMT,
        EDGE_ASSIGN,
        MATCH_BODY,
        MATCH_STMT,
        CREATE_STMT,
    };

};

#endif

