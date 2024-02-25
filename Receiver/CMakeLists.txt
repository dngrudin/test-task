cmake_minimum_required(VERSION 3.0.0)

project(Receiver)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    "main.cpp"
    "PacketReceiver.hpp"
    "PacketReceiver.cpp"
)

add_executable(receiver main.cpp ${SOURCES})
target_link_libraries(receiver Core Handlers Interfaces)

add_subdirectory("Core")
add_subdirectory("Handlers")
add_subdirectory("Interfaces")
