cmake_minimum_required(VERSION 3.8)

set(LIBRARY_NAME top5)
set(LIBRARY_ALIAS Top5)

set(SOURCE
    "private/top5.cpp"
    "private/utilites.hpp"
    "private/numbers_type_array.hpp"
    "types.hpp"
    "top5.hpp"
)

add_library(${LIBRARY_NAME} STATIC ${SOURCE})
add_library(${LIBRARY_ALIAS}::${LIBRARY_ALIAS} ALIAS ${LIBRARY_NAME})
target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})