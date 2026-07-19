# Программа вызывает библиотечные функции и обрабатывает аргументы
# командной строки; сама логика хеш-таблицы и разбора слов в неё не входит.

add_executable(word_freq src/main.c)
target_link_libraries(word_freq PRIVATE hashtable_static)
