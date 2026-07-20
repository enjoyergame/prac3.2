#!/usr/bin/env python3
"""Генератор больших текстовых файлов для нагрузочного тестирования
хеш-таблицы (миллионы слов).

Использование:
    python3 generate_test_file.py <output_path> <word_count> [vocab_size]

Пример (5 миллионов слов, словарь из 50000 уникальных слов):
    python3 generate_test_file.py big.txt 5000000 50000
"""

import random
import sys

WORDS_PER_LINE = 15


def main():
    if len(sys.argv) < 3:
        print(f"Использование: {sys.argv[0]} <output_path> <word_count> [vocab_size]")
        sys.exit(1)

    output_path = sys.argv[1]
    word_count = int(sys.argv[2])
    vocab_size = int(sys.argv[3]) if len(sys.argv) > 3 else 50000

    alphabet = "abcdefghijklmnopqrstuvwxyz"

    def make_word(index):
        # Кодируем индекс в буквенном алфавите, чтобы слово состояло
        # только из букв (парсер библиотеки выделяет слова именно так).
        digits = []
        n = index
        while True:
            digits.append(alphabet[n % 26])
            n //= 26
            if n == 0:
                break
        return "".join(reversed(digits))

    vocabulary = [make_word(i) for i in range(vocab_size)]

    with open(output_path, "w") as f:
        line_words = []
        for _ in range(word_count):
            line_words.append(random.choice(vocabulary))
            if len(line_words) >= WORDS_PER_LINE:
                f.write(" ".join(line_words) + "\n")
                line_words = []
        if line_words:
            f.write(" ".join(line_words) + "\n")


if __name__ == "__main__":
    main()
