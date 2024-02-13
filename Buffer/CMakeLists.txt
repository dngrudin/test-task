cmake_minimum_required(VERSION 3.0.0)

project(ServerBuffer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(server_buffer main.cpp)

target_link_libraries(server_buffer PUBLIC ServerUtilities::ServerUtilities)

add_subdirectory("server_utilities")
