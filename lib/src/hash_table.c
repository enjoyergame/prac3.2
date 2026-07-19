/*
Реализация хеш-таблицы со строковыми ключами.
Разрешение коллизий методом цепочек.

Кучуков Ридаль
МК-101
*/

#include "hash_table.h"

#include <stdlib.h>
#include <string.h>

static HashNode *node_create(const char *key)
{
    HashNode *node = malloc(sizeof(HashNode));
    if (!node) {
        return NULL;
    }

    size_t key_len = strlen(key);
    node->key = malloc(key_len + 1);
    if (!node->key) {
        free(node);
        return NULL;
    }
    memcpy(node->key, key, key_len + 1);

    node->count = 1;
    node->next = NULL;

    return node;
}

static void node_destroy(HashNode *node)
{
    free(node->key);
    free(node);
}
