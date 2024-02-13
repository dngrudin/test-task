cmake_minimum_required(VERSION 3.0.0)

set(EXE_NAME server)

set(SOURCES
    "main.cpp"
    "src/Server.cpp"
    "include/Server.hpp"
    "src/RingBuffer.cpp"
    "include/RingBuffer.hpp"
    "src/BufferReader.cpp"
    "include/BufferReader.hpp"
)

add_executable(${EXE_NAME} ${SOURCES})
target_link_libraries(${EXE_NAME} PUBLIC Utilities::Utilities)
target_include_directories(${EXE_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)