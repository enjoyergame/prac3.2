/*
Хеш-таблица (ассоциативный массив) со строковыми ключами.

Кучуков Ридаль
МК-101
*/

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct HashNode
{
    char *key;
    size_t count;
    struct HashNode *next;
} HashNode;

typedef struct HashTable
{
    HashNode **buckets; // массив указателей на ноды в указателях лежат списки нод
    size_t capacity;
    size_t size;
} HashTable;

HashTable *hash_table_create(size_t capacity);

void hash_table_destroy(HashTable *table);

bool hash_table_rebuild(HashTable *table, size_t new_capacity);

HashNode *hash_table_find(const HashTable *table, const char *key);

bool hash_table_insert(HashTable *table, const char *key, size_t *out_count);

bool hash_table_remove(HashTable *table, const char *key);

double hash_table_load_factor(const HashTable *table);

#endif /* HASH_TABLE_H */
