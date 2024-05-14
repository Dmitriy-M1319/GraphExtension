CREATE FUNCTION cypher(cstring, cstring)
    RETURNS cstring
AS 'MODULE_PATHNAME', 'cypher'
    LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION key_value(cstring, cstring)
    RETURNS cstring
AS 'MODULE_PATHNAME', 'cypher'
    LANGUAGE C IMMUTABLE STRICT;
