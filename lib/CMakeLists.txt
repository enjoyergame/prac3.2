# Библиотека собирается и как статическая, и как динамическая,
# из одного и того же набора исходников.

set(LIB_SOURCES
    src/hash_table.c
    src/word_stats.c
)

add_library(hashtable_static STATIC ${LIB_SOURCES})
target_include_directories(hashtable_static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_target_properties(hashtable_static PROPERTIES OUTPUT_NAME hashtable)

add_library(hashtable_shared SHARED ${LIB_SOURCES})
target_include_directories(hashtable_shared PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_target_properties(hashtable_shared PROPERTIES OUTPUT_NAME hashtable)
