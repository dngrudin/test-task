cmake_minimum_required(VERSION 3.0.0)

set(MODULE_NAME md5)
set(MODULE_ALIAS MD5)

set(OPENSSL_USE_STATIC_LIBS TRUE)
find_package(OpenSSL 3.0 REQUIRED)

set(SOURCES
    "src/MD5.cpp"
    "include/MD5.hpp"
)

add_library(${MODULE_NAME} STATIC ${SOURCES})
add_library(${GROUP_ALIAS}::${MODULE_ALIAS} ALIAS ${MODULE_NAME})
target_include_directories(${MODULE_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${MODULE_NAME} PUBLIC OpenSSL::SSL OpenSSL::Crypto)
