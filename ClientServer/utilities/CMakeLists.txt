cmake_minimum_required(VERSION 3.0.0)

set(GROUP_NAME utilities)
set(GROUP_ALIAS Utilities)

add_library(${GROUP_NAME} INTERFACE)
add_library(${GROUP_ALIAS}::${GROUP_ALIAS} ALIAS ${GROUP_NAME})
target_link_libraries(${GROUP_NAME} INTERFACE
    Utilities::MD5
    Utilities::Socket
    Utilities::DataConverter
    Utilities::Constants
    Utilities::Time
    Utilities::Thread)

add_subdirectory("md5")
add_subdirectory("socket")
add_subdirectory("data_converter")
add_subdirectory("constants")
add_subdirectory("time")
add_subdirectory("thread")