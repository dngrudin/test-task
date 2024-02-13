cmake_minimum_required(VERSION 3.0.0)

project(CommandManagerServer C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_subdirectory("lib")

add_executable(command_manager_server main.c)
target_link_libraries(command_manager_server PUBLIC CommandManager::CommandManager)
