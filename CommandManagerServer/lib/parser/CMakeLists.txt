cmake_minimum_required(VERSION 3.0.0)

set(MODULE_NAME parser)
set(MODULE_ALIAS Parser)

set(SOURCE
    "Parser.h"
    "ParserFactory.h"
    "private/ParserFactory.c"
    "private/ParserImpl.c"
    "private/ParserImpl.h"
)

add_library(${MODULE_NAME}_iface INTERFACE)
add_library(${MODULE_ALIAS}::IFace ALIAS ${MODULE_NAME}_iface)
target_include_directories(${MODULE_NAME}_iface INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(${MODULE_NAME}_factory STATIC ${SOURCE})
add_library(${MODULE_ALIAS}::Factory ALIAS ${MODULE_NAME}_factory)
target_link_libraries(${MODULE_NAME}_factory PUBLIC ${MODULE_ALIAS}::IFace)
target_include_directories(${MODULE_NAME}_factory PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
                                                  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/private)

add_library(${MODULE_NAME} INTERFACE)
add_library(${MODULE_ALIAS}::${MODULE_ALIAS} ALIAS ${MODULE_NAME})
target_link_libraries(${MODULE_NAME} INTERFACE ${MODULE_ALIAS}::Factory ${MODULE_ALIAS}::IFace)