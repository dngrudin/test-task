cmake_minimum_required(VERSION 3.0.0)

set(MODULE_NAME Interfaces)

set(SOURCES
    "IReceiver.hpp"
    "ICallback.hpp"
)

add_library(${MODULE_NAME} INTERFACE)
target_include_directories(${MODULE_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${MODULE_NAME} INTERFACE Core)