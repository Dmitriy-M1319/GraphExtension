#include <postgres.h>
#include <port.h>
#include <catalog/pg_type.h>
#include <executor/spi.h>
#include <fmgr.h>
#include <utils/numeric.h>
#include <string.h>

#define MAX_KEY_VALUE_LENGTH 512

PG_MODULE_MAGIC;

typedef struct {
    char *key;
    char *value;
} graph_key_value;

typedef struct {
    char *name;
    char *label;
    graph_key_value *body;
} graph_node;

typedef struct {
    graph_node *fst;
    graph_node *lst;
    char *label;
} graph_edge;

char *
kv_to_string(const graph_key_value *kv)
{
    char *result = (char *) palloc(MAX_KEY_VALUE_LENGTH);
    int res = pg_snprintf(result, MAX_KEY_VALUE_LENGTH, "%s:%s", kv->key, kv->value);
    if(res <= 0)
    {
        ereport(ERROR, (errcode(ERRCODE_DATA_EXCEPTION)), (errmsg("cannot write key and value in string")));
    }
    elog(INFO, "%s", result);
    return result;
}

PG_FUNCTION_INFO_V1(cypher);
PG_FUNCTION_INFO_V1(key_value);

Datum
cypher(PG_FUNCTION_ARGS) {
    char *database_name;
    char *query;

    database_name = PG_GETARG_CSTRING(0);
    query = PG_GETARG_CSTRING(1);
    elog(INFO, "%s", query);

    PG_RETURN_CSTRING(query);
}

Datum
key_value(PG_FUNCTION_ARGS) {
    char *key;
    char *value;

    key = PG_GETARG_CSTRING(0);
    value = PG_GETARG_CSTRING(1);

    graph_key_value kv = {key, value};
    elog(DEBUG1, "%s", key);
    elog(DEBUG1, "%s", value);
    char *data = kv_to_string(&kv);

    PG_RETURN_CSTRING(data);
}
