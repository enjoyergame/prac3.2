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

HashTable *hash_table_create(size_t capacity)
{
    if (capacity == 0) {
        capacity = 1;
    }

    HashTable *table = malloc(sizeof(HashTable));
    if (!table) {
        return NULL;
    }

    table->buckets = calloc(capacity, sizeof(HashNode *));
    if (!table->buckets) {
        free(table);
        return NULL;
    }

    table->capacity = capacity;
    table->size = 0;

    return table;
}

void hash_table_destroy(HashTable *table)
{
    if (!table) {
        return;
    }

    for (size_t i = 0; i < table->capacity; ++i) {
        HashNode *node = table->buckets[i];
        while (node) {
            HashNode *next = node->next;
            node_destroy(node);
            node = next;
        }
    }

    free(table->buckets);
    free(table);
}
