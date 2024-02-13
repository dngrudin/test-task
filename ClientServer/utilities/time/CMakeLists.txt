cmake_minimum_required(VERSION 3.0.0)

set(MODULE_NAME time)
set(MODULE_ALIAS Time)

set(SOURCES
    "src/Time.cpp"
    "include/Time.hpp"
)

add_library(${MODULE_NAME} STATIC ${SOURCES})
add_library(${GROUP_ALIAS}::${MODULE_ALIAS} ALIAS ${MODULE_NAME})
target_include_directories(${MODULE_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
