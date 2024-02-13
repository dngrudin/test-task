cmake_minimum_required(VERSION 3.0.0)

set(MODULE_NAME constants)
set(MODULE_ALIAS Constants)

add_library(${MODULE_NAME} INTERFACE)
add_library(${GROUP_ALIAS}::${MODULE_ALIAS} ALIAS ${MODULE_NAME})
target_include_directories(${MODULE_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
