cmake_minimum_required(VERSION 3.0.0)

set(EXE_NAME client)

set(SOURCES
    "main.cpp"
    "src/Client.cpp"
    "include/Client.hpp"
    "src/DataPull.cpp"
    "include/DataPull.hpp"
)

add_executable(${EXE_NAME} ${SOURCES})
target_link_libraries(${EXE_NAME} PUBLIC Utilities::Utilities)
target_include_directories(${EXE_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
