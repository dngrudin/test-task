
#ifndef ELEVATOR_MOCK_H
#define ELEVATOR_MOCK_H

#include <gmock/gmock.h>

#include "IElevator.hpp"

namespace mock
{
    class ElevatorMock : public elevator::IElevator
    {
    public:
        MOCK_METHOD(elevator::FloorNumber, getCurrentFloor, (), (const, override));
        MOCK_METHOD(elevator::ElevatorStatus, getCurrentStatus, (), (const, override));
        MOCK_METHOD(bool, isFull, (), (const, override));
        MOCK_METHOD(bool, call, (elevator::FloorNumber, elevator::FloorNumber), (override));
    };

}

#endif // ELEVATOR_MOCK_H