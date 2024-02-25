cmake_minimum_required(VERSION 3.0.0)

set(MODULE_NAME Handlers)

set(SOURCES
    "BinarySizeParsing.hpp"
    "FindBinaryEnd.hpp"
    "FindTextEnd.hpp"
    "PakageComplete.hpp"
    "TypeDetection.hpp"
)

add_library(${MODULE_NAME} INTERFACE)
target_include_directories(${MODULE_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${MODULE_NAME} INTERFACE Core)