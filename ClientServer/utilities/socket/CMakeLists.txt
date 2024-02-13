cmake_minimum_required(VERSION 3.0.0)

set(MODULE_NAME socket)
set(MODULE_ALIAS Socket)

set(SOURCES
    "src/UdpSocket.cpp"
    "include/UdpSocket.hpp"
)

add_library(${MODULE_NAME} STATIC ${SOURCES})
add_library(${GROUP_ALIAS}::${MODULE_ALIAS} ALIAS ${MODULE_NAME})
target_include_directories(${MODULE_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
