cmake_minimum_required(VERSION 3.0.0)

project(ClientServer CXX)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory("utilities")
add_subdirectory("client")
add_subdirectory("server")