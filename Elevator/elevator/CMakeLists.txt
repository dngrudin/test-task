cmake_minimum_required(VERSION 3.8)

set(LIBRARY_NAME elevator)
set(LIBRARY_ALIAS Elevator)

set(SOURCE
    "private/CallerToFloor.cpp"
    "private/Elevator.cpp"
    "private/ElevatorsControl.cpp"
    "private/EventLogger.cpp"
    "CallerToFloor.hpp"
    "Elevator.hpp"
    "ElevatorsControl.hpp"
    "EventLogger.hpp"
    "ICallerToFloor.hpp"
    "IElevator.hpp"
    "IElevatorsControl.hpp"
    "IEventLogger.hpp"
    "Types.hpp"
)

add_library(${LIBRARY_NAME} STATIC ${SOURCE})
add_library(${LIBRARY_ALIAS}::${LIBRARY_ALIAS} ALIAS ${LIBRARY_NAME})
target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})