cmake_minimum_required(VERSION 3.8)

set(SOURCE_TEST
    "main_test.cpp"
    "mocks/CallerToFloorMock.hpp"
    "mocks/ElevatorMock.hpp"
    "mocks/ElevatorsControlMock.hpp"
    "mocks/EventLoggerMock.hpp"
    "testElevatorsControl.cpp"
    "testElevatorsControl.hpp"
    "testElevator.cpp"
    "testElevator.hpp"
)

add_executable(${EXE_NAME}_test ${SOURCE_TEST})
target_link_libraries(${EXE_NAME}_test PUBLIC Elevator::Elevator gtest gmock)

add_test(NAME ${EXE_NAME}_test COMMAND ${EXE_NAME}_test)
