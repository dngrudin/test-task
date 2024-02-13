

#include "testElevator.hpp"

using ::testing::AtLeast;
using ::testing::Return;
using ::testing::_;

namespace utest
{
    void ElevatorFixture::SetUp()
    {
        elevator::ElevatorParameter parameter{ 5, scElevatorSpeed };

        mEventLoggerMock = std::make_shared<mock::EventLoggerMock>();
        mElevator = std::make_shared<elevator::Elevator>(1, parameter, mEventLoggerMock);
    }

    void ElevatorFixture::TearDown()
    {
        mElevator.reset();
        mEventLoggerMock.reset();
    }


    TEST_F(ElevatorFixture, testRecallBeforeFirstPassenger)
    {
        EXPECT_CALL(*mEventLoggerMock, addEvent(_, _, _, _))
            .Times(AtLeast(1));
        EXPECT_CALL(*mEventLoggerMock, getEvents(_))
            .Times(0);
        EXPECT_CALL(*mEventLoggerMock, clearEvents())
            .Times(0);

        EXPECT_TRUE(mElevator->call(4, 9));
        EXPECT_FALSE(mElevator->call(3, 9));

        std::this_thread::sleep_for(2 * scElevatorSpeed);
    }

    TEST_F(ElevatorFixture, testRecallAfterFirstPassenger)
    {
        EXPECT_CALL(*mEventLoggerMock, addEvent(_, _, _, _))
            .Times(AtLeast(1));
        EXPECT_CALL(*mEventLoggerMock, getEvents(_))
            .Times(0);
        EXPECT_CALL(*mEventLoggerMock, clearEvents())
            .Times(0);

        EXPECT_TRUE(mElevator->call(1, 9));

        std::this_thread::sleep_for(2 * scElevatorSpeed);

        EXPECT_TRUE(mElevator->call(5, 7));
    }

    TEST_F(ElevatorFixture, testCallInOtherDirection)
    {
        EXPECT_CALL(*mEventLoggerMock, addEvent(_, _, _, _))
            .Times(AtLeast(1));
        EXPECT_CALL(*mEventLoggerMock, getEvents(_))
            .Times(0);
        EXPECT_CALL(*mEventLoggerMock, clearEvents())
            .Times(0);

        EXPECT_TRUE(mElevator->call(1, 9));

        std::this_thread::sleep_for(4 * scElevatorSpeed);

        EXPECT_FALSE(mElevator->call(3, 1));
    }

}
