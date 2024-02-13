cmake_minimum_required(VERSION 3.0.0)

set(MODULE_NAME bloks_info)
set(MODULE_ALIAS BloksInfo)

set(SOURCES
    "src/BlockInfo.cpp"
    "include/BlockInfo.hpp"
)

add_library(${MODULE_NAME} STATIC ${SOURCES})
add_library(${MODULE_ALIAS}::${MODULE_ALIAS} ALIAS ${MODULE_NAME})
target_include_directories(${MODULE_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
