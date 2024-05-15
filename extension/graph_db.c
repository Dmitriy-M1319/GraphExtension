#include <postgres.h>
#include <port.h>
#include <fmgr.h>
#include <utils/builtins.h>
#include <string.h>

#define MAX_KEY_VALUE_LENGTH 512
#define DEBUG

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
    char *obj_name;
    char *label;
    char *body;
} node;

typedef struct {
    graph_node *fst;
    graph_node *lst;
    char *label;
} graph_edge;

char *
kv_to_string(const graph_key_value *kv) {
    size_t len = sizeof(char) * (strlen(kv->key) + strlen(kv->value) + 2);
    char *buf = (char *) malloc(len);
    int res = 0;
    if ((res = snprintf(buf, len,
                        "%s:%s", kv->key, kv->value)) <= 0) {
        perror("failed to write key-value to string");
        free(buf);
        return NULL;
    }
    return buf;
}

char *
body_to_string(const graph_key_value *body, unsigned int size) {
    char smalltab[] = "    ";
    char *buf = (char *) malloc(MAX_KEY_VALUE_LENGTH);
    char *curr = buf;
    *(curr++) = '{';
    *(curr++) = '\n';
    for (int i = 0; i < size; ++i) {
        char *kv_str = kv_to_string(&body[i]);
        size_t s_len = strlen(kv_str);
        memcpy(curr, smalltab, strlen(smalltab));
        curr += strlen(smalltab);
        memcpy(curr, kv_str, s_len);
        curr += s_len;
        *(curr++) = ',';
        *(curr++) = '\n';
        free(kv_str);
    }
    *(curr - 2) = ' ';
    *curr = '}';
    return buf;
}


PG_FUNCTION_INFO_V1(cypher);

PG_FUNCTION_INFO_V1(key_value);

PG_FUNCTION_INFO_V1(graph_nodes);

PG_FUNCTION_INFO_V1(graph_node_in);

PG_FUNCTION_INFO_V1(graph_node_out);
#ifndef DEBUG
PG_FUNCTION_INFO_V1(filter_graph_nodes);
PG_FUNCTION_INFO_V1(graph_edges);
PG_FUNCTION_INFO_V1(filter_graph_edges);
PG_FUNCTION_INFO_V1(create_graph);
#endif

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
    char result[MAX_KEY_VALUE_LENGTH];

    key = PG_GETARG_CSTRING(0);
    value = PG_GETARG_CSTRING(1);

    graph_key_value kv = {key, value};
    elog(DEBUG1, "%s", key);
    elog(DEBUG1, "%s", value);

    char *data = kv_to_string(&kv);
    memcpy(result, data, MAX_KEY_VALUE_LENGTH);
    free(data);

    PG_RETURN_CSTRING(result);
}

Datum
graph_nodes(PG_FUNCTION_ARGS) {
    char body[MAX_KEY_VALUE_LENGTH];
    graph_key_value kv[5] = {
            {"key1", "value1"},
            {"key2", "value2"},
            {"key3", "value3"},
            {"key4", "value4"},
            {"key5", "value5"},
    };

    char *b = body_to_string(kv, 5);
    memcpy(body, b, MAX_KEY_VALUE_LENGTH);
    free(b);
    //graph_node n = {"p1", "Parent", kv};

    node *result = (node *) palloc(sizeof(node));
    result->obj_name = palloc(strlen("p1") + 1);
    strcpy(result->obj_name, "p1");
    result->label = palloc(strlen("Label") + 1);
    strcpy(result->label, "Label");
    result->label = palloc(strlen(b) + 1);
    strncpy(result->body, b, strlen(b));
    PG_RETURN_POINTER(result);
}

Datum
graph_node_in(PG_FUNCTION_ARGS) {
    node *result;
    result = (node *) palloc(sizeof(node));
    char *data = PG_GETARG_CSTRING(0);
    elog(INFO, "%s", data);
    char *curr = data;
    int curr_len = 0;
    for(;*curr != '-'; ++curr, ++curr_len) {}
    result->obj_name = (char *)palloc(curr_len + 1);
    memset(result->obj_name, 0, curr_len + 1);
    strncpy(result->obj_name, data, curr_len);
    elog(INFO, "%s", result->obj_name);
    elog(INFO, "%d", strlen(result->obj_name));
    ++curr;

    char *label = curr;
    curr_len = 0;
    for(;*curr != '-'; ++curr, ++curr_len) {}
    result->label = (char *)palloc(curr_len + 1);
    memset(result->label, 0, curr_len + 1);
    strncpy(result->label, label, curr_len);
    elog(INFO, "%s", result->label);
    elog(INFO, "%d", strlen(result->label));
    ++curr;

    char *body = curr;
    curr_len = 0;
    while(*curr) {
        ++curr;
        ++curr_len;
    }
    result->body = (char *)palloc(curr_len + 1);
    memset(result->body, 0, curr_len + 1);
    strncpy(result->body, body, curr_len);
    elog(INFO, "%s", result->body);
    elog(INFO, "%d", strlen(result->body));
    PG_RETURN_POINTER(result);
}

Datum
graph_node_out(PG_FUNCTION_ARGS) {
    node *n = (node *)PG_GETARG_POINTER(0);
    char *result = psprintf("%s-%s-%s)", n->obj_name, n->label, n->body);
    PG_RETURN_CSTRING(result);
}

#ifndef DEBUG
Datum
filter_graph_nodes_by(PG_FUNCTION_ARGS) {

}

Datum
graph_edges(PG_FUNCTION_ARGS) {

}

Datum
filter_graph_edges(PG_FUNCTION_ARGS) {

}

Datum
create_graph(PG_FUNCTION_ARGS) {

}
#endif