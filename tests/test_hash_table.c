/*
Тесты хеш-таблицы и модуля подсчёта слов.

Кучуков Ридаль
МК-101
*/

#include "hash_table.h"
#include "word_stats.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

static void test_create_destroy(void)
{
    HashTable *table = hash_table_create(4);
    assert(table != NULL);
    assert(table->size == 0);
    assert(table->capacity == 4);
    hash_table_destroy(table);
}

static void test_insert_and_find(void)
{
    HashTable *table = hash_table_create(4);

    size_t count = 0;
    assert(hash_table_insert(table, "hello", &count));
    assert(count == 1);
    assert(hash_table_insert(table, "hello", &count));
    assert(count == 2);
    assert(hash_table_insert(table, "world", NULL));

    HashNode *node = hash_table_find(table, "hello");
    assert(node != NULL);
    assert(node->count == 2);
    assert(strcmp(node->key, "hello") == 0);

    assert(hash_table_find(table, "missing") == NULL);
    assert(table->size == 2);

    hash_table_destroy(table);
}

static void test_remove(void)
{
    HashTable *table = hash_table_create(4);
    hash_table_insert(table, "a", NULL);
    hash_table_insert(table, "b", NULL);

    assert(hash_table_remove(table, "a"));
    assert(hash_table_find(table, "a") == NULL);
    assert(table->size == 1);
    assert(!hash_table_remove(table, "a"));

    hash_table_destroy(table);
}

/* Специально создаём таблицу с одной корзиной, чтобы все ключи
   попали в одну цепочку, и проверяем, что коллизии обрабатываются. */
static void test_collisions_chaining(void)
{
    HashTable *table = hash_table_create(1);

    for (int i = 0; i < 20; ++i)
    {
        char key[8];
        snprintf(key, sizeof(key), "k%d", i);
        assert(hash_table_insert(table, key, NULL));
    }

    assert(table->size == 20);
    for (int i = 0; i < 20; ++i)
    {
        char key[8];
        snprintf(key, sizeof(key), "k%d", i);
        assert(hash_table_find(table, key) != NULL);
    }

    hash_table_destroy(table);
}

static void test_rebuild(void)
{
    HashTable *table = hash_table_create(2);
    for (int i = 0; i < 10; ++i)
    {
        char key[8];
        snprintf(key, sizeof(key), "x%d", i);
        hash_table_insert(table, key, NULL);
    }

    /* При вставке таблица должна была сама вырасти. */
    assert(table->capacity > 2);
    assert(table->size == 10);

    for (int i = 0; i < 10; ++i)
    {
        char key[8];
        snprintf(key, sizeof(key), "x%d", i);
        assert(hash_table_find(table, key) != NULL);
    }

    /* Явный вызов перестроения. */
    assert(hash_table_rebuild(table, 3));
    assert(table->capacity == 3);
    assert(table->size == 10);

    hash_table_destroy(table);
}

static void test_word_stats(void)
{
    const char *path = "test_fixture.txt";
    FILE *f = fopen(path, "w");
    assert(f != NULL);
    fputs("The quick brown fox. The FOX jumps over the lazy dog, the dog barks!", f);
    fclose(f);

    HashTable *table = hash_table_create(16);
    size_t total = 0;
    assert(word_stats_process_file(table, path, &total));

    assert(total == 14);

    HashNode *the_node = hash_table_find(table, "the");
    assert(the_node != NULL);
    assert(the_node->count == 4);

    HashNode *fox_node = hash_table_find(table, "fox");
    assert(fox_node != NULL);
    assert(fox_node->count == 2);

    WordCount top[3];
    size_t got = word_stats_top_n(table, top, 3);
    assert(got == 3);
    assert(strcmp(top[0].word, "the") == 0);

    hash_table_destroy(table);
    remove(path);
}

int main(void)
{
    test_create_destroy();
    test_insert_and_find();
    test_remove();
    test_collisions_chaining();
    test_rebuild();
    test_word_stats();

    printf("all tests passed successfully\n");
    return 0;
}
