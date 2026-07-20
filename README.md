# Ассоциативный массив на основе хеш-таблицы (задание 4.3)

Реализация хеш-таблицы со строковыми ключами и разрешением коллизий
методом цепочек, плюс программа подсчёта частоты слов в текстовом файле.

## Сборка

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

Результат:

- `lib/libhashtable.a`, `lib/libhashtable.so` — библиотека
- `app/word_freq` — программа
- `tests/test_hash_table` — тесты

## Запуск

```bash
./app/word_freq <путь_к_файлу> [top_n]
```

`top_n` — сколько самых частых слов вывести (по умолчанию 10).

Пример:

```bash
./app/word_freq text.txt 20
```

Тесты:

```bash
./tests/test_hash_table
```

Генерация большого файла для нагрузочного теста (проверено на 5 млн слов,
обработка укладывается в доли секунды):

```bash
python3 ../tools/generate_test_file.py big.txt 5000000 100000
./app/word_freq big.txt 10
```