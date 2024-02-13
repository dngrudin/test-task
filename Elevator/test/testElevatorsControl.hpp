
#ifndef TEST_ELEVATOR_CONTROL_H
#define TEST_ELEVATOR_CONTROL_H

#include <memory>

#include <gtest/gtest.h>

#include "mocks/ElevatorMock.hpp"
#include "ElevatorsControl.hpp"

namespace utest
{
    class ElevatorsControlFixture : public testing::Test
    {
    public:
        void SetUp() override;

        void TearDown() override;

    protected:
        std::shared_ptr<mock::ElevatorMock> mElevatorMock1;
        std::shared_ptr<mock::ElevatorMock> mElevatorMock2;
        std::shared_ptr<mock::ElevatorMock> mElevatorMock3;

        elevator::ElevatorsControl elevatorsControl;
    };

}

#endif // TEST_ELEVATOR_CONTROL_H
