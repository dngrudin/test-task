cmake_minimum_required (VERSION 3.8)

set(SOURCE_TEST
    "main_test.cpp"
    "testTop5.cpp"
    "testTop5.hpp"
)

add_executable(${EXE_NAME}_test ${SOURCE_TEST})

add_test(NAME ${EXE_NAME}_test COMMAND ${EXE_NAME}_test)

target_link_libraries(${EXE_NAME}_test PUBLIC Top5::Top5 gtest gmock)