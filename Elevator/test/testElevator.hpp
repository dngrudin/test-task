
#ifndef TEST_ELEVATOR_H
#define TEST_ELEVATOR_H

#include <memory>

#include <gtest/gtest.h>

#include "mocks/EventLoggerMock.hpp"
#include "Elevator.hpp"

using namespace std::chrono_literals;

namespace utest
{
    class ElevatorFixture : public testing::Test
    {
    public:
        void SetUp() override;

        void TearDown() override;

    protected:
        static constexpr std::chrono::seconds scElevatorSpeed = 2s;

        std::shared_ptr<mock::EventLoggerMock> mEventLoggerMock;
        std::shared_ptr<elevator::Elevator> mElevator;
    };

}

#endif // TEST_ELEVATOR_H
