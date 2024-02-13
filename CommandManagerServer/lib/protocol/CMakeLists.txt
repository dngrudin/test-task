cmake_minimum_required(VERSION 3.0.0)

set(MODULE_NAME protocol)
set(MODULE_ALIAS Protocol)

set(SOURCE
    "Protocol.h"
    "ProtocolFactory.h"
    "private/ProtocolFactory.c"
    "private/ProtocolImpl.c"
    "private/ProtocolImpl.h"
)

add_library(${MODULE_NAME}_iface INTERFACE)
add_library(${MODULE_ALIAS}::IFace ALIAS ${MODULE_NAME}_iface)
target_include_directories(${MODULE_NAME}_iface INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${MODULE_NAME}_iface INTERFACE
    CommandHandlers::IFace
    CommandProcessing::IFace
    Parser::IFace
)

add_library(${MODULE_NAME}_factory STATIC ${SOURCE})
add_library(${MODULE_ALIAS}::Factory ALIAS ${MODULE_NAME}_factory)
target_link_libraries(${MODULE_NAME}_factory PUBLIC ${MODULE_ALIAS}::IFace)
target_include_directories(${MODULE_NAME}_factory PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
                                                  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/private)

target_link_libraries(${MODULE_NAME}_factory INTERFACE
    CommandHandlers::Factory
    CommandProcessing::Factory
    Parser::Factory
)

add_library(${MODULE_NAME} INTERFACE)
add_library(${MODULE_ALIAS}::${MODULE_ALIAS} ALIAS ${MODULE_NAME})
target_link_libraries(${MODULE_NAME} INTERFACE ${MODULE_ALIAS}::Factory ${MODULE_ALIAS}::IFace)