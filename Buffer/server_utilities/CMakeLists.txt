cmake_minimum_required(VERSION 3.0.0)

set(MODULE_NAME server_utilities)
set(MODULE_ALIAS ServerUtilities)

add_library(${MODULE_NAME} INTERFACE)
add_library(${MODULE_ALIAS}::${MODULE_ALIAS} ALIAS ${MODULE_NAME})
target_link_libraries(${MODULE_NAME} INTERFACE
    BloksInfo::BloksInfo
    Buffer::Buffer
)

add_subdirectory("blocks")
add_subdirectory("buffer")