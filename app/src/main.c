/*
Программа подсчёта частоты слов в текстовом файле
на основе библиотеки хеш-таблицы.

Кучуков Ридаль
МК-101
*/

#include "hash_table.h"
#include "word_stats.h"

#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_INITIAL_CAPACITY 1024
#define DEFAULT_TOP_N 10

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "usage: %s <path to file> [top_n]\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t top_n = DEFAULT_TOP_N;
    if (argc >= 3)
    {
        top_n = (size_t)atoi(argv[2]);
    }

    HashTable *table = hash_table_create(DEFAULT_INITIAL_CAPACITY);
    if (!table)
    {
        fprintf(stderr, "Unable to allocate memory to the table\n");
        return EXIT_FAILURE;
    }

    size_t total_words = 0;
    if (!word_stats_process_file(table, argv[1], &total_words))
    {
        fprintf(stderr, "Unable to open file: %s\n", argv[1]);
        hash_table_destroy(table);
        return EXIT_FAILURE;
    }

    printf("Total words (with duplicates): %zu\n", total_words);
    printf("Unique words:              %zu\n", table->size);
    printf("Table capacity: %zu, load factor: %.3f\n",
           table->capacity, hash_table_load_factor(table));

    if (top_n > 0)
    {
        WordCount *top = malloc(top_n * sizeof(WordCount));
        if (top)
        {
            size_t got = word_stats_top_n(table, top, top_n);
            printf("\nTop-%zu words:\n", got);
            for (size_t i = 0; i < got; ++i)
            {
                printf("%2zu. %-20s %zu\n", i + 1, top[i].word, top[i].count);
            }
            free(top);
        }
    }

    hash_table_destroy(table);
    return EXIT_SUCCESS;
}
