cmake_minimum_required(VERSION 3.15)
project(hash_table_word_freq C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

add_compile_options(-Wall -Wextra)

add_subdirectory(lib)
add_subdirectory(app)

option(BUILD_TESTS "Собирать тестовый исполняемый файл" ON)
if(BUILD_TESTS)
    add_subdirectory(tests)
endif()
