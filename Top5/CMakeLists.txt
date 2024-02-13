cmake_minimum_required(VERSION 3.8)

project("Top5" CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXE_NAME top5matrix)

add_executable(${EXE_NAME} "main.cpp")
target_link_libraries(${EXE_NAME} PUBLIC Top5::Top5)

add_subdirectory("top5")

find_package(GTest REQUIRED)
enable_testing()
add_subdirectory("test")
