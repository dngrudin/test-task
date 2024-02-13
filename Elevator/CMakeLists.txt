cmake_minimum_required(VERSION 3.8)

project("Elevator" CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXE_NAME elevator_control)

add_executable(${EXE_NAME} "main.cpp")
target_link_libraries(${EXE_NAME} PUBLIC Elevator::Elevator)

add_subdirectory("elevator")

find_package(GTest REQUIRED)
enable_testing()
add_subdirectory("test")
