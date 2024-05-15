CREATE TYPE graph_node;

CREATE FUNCTION cypher(cstring, cstring)
    RETURNS cstring
AS 'MODULE_PATHNAME', 'cypher'
    LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION key_value(cstring, cstring)
    RETURNS cstring
AS 'MODULE_PATHNAME', 'key_value'
    LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION graph_nodes()
    RETURNS graph_node
AS 'MODULE_PATHNAME', 'graph_nodes'
    LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION graph_node_in(cstring)
    RETURNS graph_node
AS 'MODULE_PATHNAME', 'graph_node_in'
    LANGUAGE C STRICT IMMUTABLE;

CREATE FUNCTION graph_node_out(graph_node)
    RETURNS cstring
AS 'MODULE_PATHNAME', 'graph_node_out'
    LANGUAGE C STRICT IMMUTABLE;

CREATE TYPE graph_node (
    INTERNALLENGTH = -1,
    INPUT = graph_node_in,
    OUTPUT = graph_node_out,
    STORAGE = extended -- try to compress
);