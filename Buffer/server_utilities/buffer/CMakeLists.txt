cmake_minimum_required(VERSION 3.0.0)

set(MODULE_NAME buffer)
set(MODULE_ALIAS Buffer)

set(SOURCES
    "src/BufferFiller.cpp"
    "include/BufferFiller.hpp"
    "src/FileReader.cpp"
    "include/FileReader.hpp"
)

add_library(${MODULE_NAME} STATIC ${SOURCES})
add_library(${MODULE_ALIAS}::${MODULE_ALIAS} ALIAS ${MODULE_NAME})
target_include_directories(${MODULE_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${MODULE_NAME} PUBLIC BloksInfo::BloksInfo)