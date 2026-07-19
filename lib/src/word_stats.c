/*
Разбор текстового файла на слова и подсчёт частоты слов
с использованием хеш-таблицы.

Кучуков Ридаль
МК-101
*/

#include "word_stats.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>


#define WORD_STATS_MAX_WORD_LENGTH 127

bool word_stats_process_file(HashTable *table, const char *filepath, size_t *out_total_words)
{
    FILE *file = fopen(filepath, "r");
    if (!file) {
        return false;
    }

    char buffer[WORD_STATS_MAX_WORD_LENGTH + 1];
    size_t buffer_len = 0;
    size_t total_words = 0;
    int c;

    while ((c = fgetc(file)) != EOF) {
        if (isalpha((unsigned char)c)) {
            if (buffer_len < WORD_STATS_MAX_WORD_LENGTH) {
                buffer[buffer_len++] = (char)tolower((unsigned char)c);
            }
        } else if (buffer_len > 0) {
            buffer[buffer_len] = '\0';
            hash_table_insert(table, buffer, NULL);
            total_words += 1;
            buffer_len = 0;
        }
    }

    if (buffer_len > 0) {
        buffer[buffer_len] = '\0';
        hash_table_insert(table, buffer, NULL);
        total_words += 1;
    }

    fclose(file);

    if (out_total_words) {
        *out_total_words = total_words;
    }

    return true;
}