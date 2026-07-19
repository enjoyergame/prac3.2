/*
Разбор текстового файла на слова и подсчёт частоты слов
с использованием хеш-таблицы.

Кучуков Ридаль
МК-101
*/

#ifndef WORD_STATS_H
#define WORD_STATS_H

#include "hash_table.h"

#include <stdio.h>

typedef struct WordCount
{
    const char *word;
    size_t count;
} WordCount;

bool word_stats_process_file(HashTable *table, const char *filepath, size_t *out_total_words);

size_t word_stats_top_n(const HashTable *table, WordCount *out_array, size_t n);

#endif /* WORD_STATS_H */
