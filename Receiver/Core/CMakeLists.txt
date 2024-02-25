cmake_minimum_required(VERSION 3.0.0)

set(MODULE_NAME Core)

set(SOURCES
    "Action.hpp"
    "Buffer.hpp"
    "Byte.hpp"
    "PacketState.hpp"
    "PayloadRange.hpp"
)

add_library(${MODULE_NAME} INTERFACE)
target_include_directories(${MODULE_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
