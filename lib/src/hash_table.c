/*
Реализация хеш-таблицы со строковыми ключами.
Разрешение коллизий методом цепочек.

Кучуков Ридаль
МК-101
*/

#include "hash_table.h"

#include <stdlib.h>
#include <string.h>

#define HASH_TABLE_LOAD_FACTOR_LIMIT 0.75
#define HASH_TABLE_GROWTH_FACTOR 2

static unsigned long hash_string(const char *key)
{
    unsigned long hash = 5381;
    int c;

    while ((c = (unsigned char)*key++) != 0)
    {
        hash = ((hash << 5) + hash) + (unsigned long)c;
    }

    return hash;
}

static HashNode *node_create(const char *key)
{
    HashNode *node = malloc(sizeof(HashNode));
    if (!node)
    {
        return NULL;
    }

    size_t key_len = strlen(key);
    node->key = malloc(key_len + 1);
    if (!node->key)
    {
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
    if (capacity == 0)
    {
        capacity = 1;
    }

    HashTable *table = malloc(sizeof(HashTable));
    if (!table)
    {
        return NULL;
    }

    table->buckets = calloc(capacity, sizeof(HashNode *));
    if (!table->buckets)
    {
        free(table);
        return NULL;
    }

    table->capacity = capacity;
    table->size = 0;

    return table;
}

void hash_table_destroy(HashTable *table)
{
    if (!table)
    {
        return;
    }

    for (size_t i = 0; i < table->capacity; ++i)
    {
        HashNode *node = table->buckets[i];
        while (node)
        {
            HashNode *next = node->next;
            node_destroy(node);
            node = next;
        }
    }

    free(table->buckets);
    free(table);
}

double hash_table_load_factor(const HashTable *table)
{
    return (double)table->size / (double)table->capacity;
}

bool hash_table_rebuild(HashTable *table, size_t new_capacity)
{
    if (new_capacity == 0)
    {
        return false;
    }

    HashNode **new_buckets = calloc(new_capacity, sizeof(HashNode *));
    if (!new_buckets)
    {
        return false;
    }

    for (size_t i = 0; i < table->capacity; ++i)
    {
        HashNode *node = table->buckets[i];
        while (node)
        {
            HashNode *next = node->next;
            size_t new_index = hash_string(node->key) % new_capacity;
            node->next = new_buckets[new_index];
            new_buckets[new_index] = node;
            node = next;
        }
    }

    free(table->buckets);
    table->buckets = new_buckets;
    table->capacity = new_capacity;

    return true;
}
HashNode *hash_table_find(const HashTable *table, const char *key)
{
    size_t index = hash_string(key) % table->capacity;
    HashNode *node = table->buckets[index];

    while (node)
    {
        if (strcmp(node->key, key) == 0)
        {
            return node;
        }
        node = node->next;
    }

    return NULL;
}

bool hash_table_insert(HashTable *table, const char *key, size_t *out_count)
{
    HashNode *existing = hash_table_find(table, key);
    if (existing)
    {
        existing->count += 1;
        if (out_count)
        {
            *out_count = existing->count;
        }
        return true;
    }

    HashNode *node = node_create(key);
    if (!node)
    {
        return false;
    }

    if (hash_table_load_factor(table) >= HASH_TABLE_LOAD_FACTOR_LIMIT)
    {
        hash_table_rebuild(table, table->capacity * HASH_TABLE_GROWTH_FACTOR);
    }

    size_t index = hash_string(key) % table->capacity;
    node->next = table->buckets[index];
    table->buckets[index] = node;
    table->size += 1;

    if (out_count)
    {
        *out_count = node->count;
    }

    return true;
}

bool hash_table_remove(HashTable *table, const char *key)
{
    size_t index = hash_string(key) % table->capacity;
    HashNode *node = table->buckets[index];
    HashNode *prev = NULL;

    while (node)
    {
        if (strcmp(node->key, key) == 0)
        {
            if (prev)
            {
                prev->next = node->next;
            }
            else
            {
                table->buckets[index] = node->next;
            }
            node_destroy(node);
            table->size -= 1;
            return true;
        }
        prev = node;
        node = node->next;
    }

    return false;
}
