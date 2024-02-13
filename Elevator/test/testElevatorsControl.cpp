
#include "testElevatorsControl.hpp"

using ::testing::Return;
using ::testing::_;

namespace utest
{
    void ElevatorsControlFixture::SetUp()
    {
        mElevatorMock1 = std::make_shared<mock::ElevatorMock>();
        mElevatorMock2 = std::make_shared<mock::ElevatorMock>();
        mElevatorMock3 = std::make_shared<mock::ElevatorMock>();

        elevatorsControl.setElevators({ mElevatorMock1, mElevatorMock2, mElevatorMock3 });
    }

    void ElevatorsControlFixture::TearDown()
    {
        mElevatorMock1.reset();
        mElevatorMock2.reset();
        mElevatorMock3.reset();

        elevatorsControl.setElevators({ });
    }


    TEST_F(ElevatorsControlFixture, testCall)
    {
        elevator::FloorNumber from = 1;
        elevator::FloorNumber to = 5;

        EXPECT_CALL(*mElevatorMock1, getCurrentFloor())
            .Times(1)
            .WillOnce(Return(elevator::FloorNumber(1)));
        EXPECT_CALL(*mElevatorMock1, getCurrentStatus())
            .Times(1)
            .WillOnce(Return(elevator::ElevatorStatus::Wait));
        EXPECT_CALL(*mElevatorMock1, isFull())
            .Times(1)
            .WillOnce(Return(false));
        EXPECT_CALL(*mElevatorMock1, call(from, to))
            .Times(1)
            .WillOnce(Return(true));

        EXPECT_CALL(*mElevatorMock2, getCurrentFloor())
            .Times(1)
            .WillOnce(Return(elevator::FloorNumber(1)));
        EXPECT_CALL(*mElevatorMock2, getCurrentStatus())
            .Times(1)
            .WillOnce(Return(elevator::ElevatorStatus::Wait));
        EXPECT_CALL(*mElevatorMock2, isFull())
            .Times(1)
            .WillOnce(Return(false));
        EXPECT_CALL(*mElevatorMock2, call(_, _))
            .Times(0);

        EXPECT_CALL(*mElevatorMock3, getCurrentFloor())
            .Times(1)
            .WillOnce(Return(elevator::FloorNumber(1)));
        EXPECT_CALL(*mElevatorMock3, getCurrentStatus())
            .Times(1)
            .WillOnce(Return(elevator::ElevatorStatus::Wait));
        EXPECT_CALL(*mElevatorMock3, isFull())
            .Times(1)
            .WillOnce(Return(false));
        EXPECT_CALL(*mElevatorMock3, call(_, _))
            .Times(0);

        elevatorsControl.callElevator(from, to, elevator::SelectDirection::Up);
    }

    TEST_F(ElevatorsControlFixture, testPickUpPassengerInDirectionOfElevatorMovement)
    {
        elevator::FloorNumber from = 5;
        elevator::FloorNumber to = 7;

        EXPECT_CALL(*mElevatorMock1, getCurrentFloor())
            .Times(1)
            .WillOnce(Return(elevator::FloorNumber(3)));
        EXPECT_CALL(*mElevatorMock1, getCurrentStatus())
            .Times(1)
            .WillOnce(Return(elevator::ElevatorStatus::MoveUp));
        EXPECT_CALL(*mElevatorMock1, isFull())
            .Times(1)
            .WillOnce(Return(false));
        EXPECT_CALL(*mElevatorMock1, call(from, to))
            .Times(1)
            .WillOnce(Return(true));

        EXPECT_CALL(*mElevatorMock2, getCurrentFloor())
            .Times(1)
            .WillOnce(Return(elevator::FloorNumber(1)));
        EXPECT_CALL(*mElevatorMock2, getCurrentStatus())
            .Times(1)
            .WillOnce(Return(elevator::ElevatorStatus::Wait));
        EXPECT_CALL(*mElevatorMock2, isFull())
            .Times(1)
            .WillOnce(Return(false));
        EXPECT_CALL(*mElevatorMock2, call(_, _))
            .Times(0);

        EXPECT_CALL(*mElevatorMock3, getCurrentFloor())
            .Times(1)
            .WillOnce(Return(elevator::FloorNumber(1)));
        EXPECT_CALL(*mElevatorMock3, getCurrentStatus())
            .Times(1)
            .WillOnce(Return(elevator::ElevatorStatus::Wait));
        EXPECT_CALL(*mElevatorMock3, isFull())
            .Times(1)
            .WillOnce(Return(false));
        EXPECT_CALL(*mElevatorMock3, call(_, _))
            .Times(0);

        elevatorsControl.callElevator(from, to, elevator::SelectDirection::Up);
    }

    TEST_F(ElevatorsControlFixture, testDoNotPickUpPassengerAgainstDirectionOfMovementOfElevator)
    {
        elevator::FloorNumber from = 5;
        elevator::FloorNumber to = 7;

        EXPECT_CALL(*mElevatorMock1, getCurrentFloor())
            .Times(1)
            .WillOnce(Return(elevator::FloorNumber(6)));
        EXPECT_CALL(*mElevatorMock1, getCurrentStatus())
            .Times(1)
            .WillOnce(Return(elevator::ElevatorStatus::MoveDown));
        EXPECT_CALL(*mElevatorMock1, isFull())
            .Times(1)
            .WillOnce(Return(false));
        EXPECT_CALL(*mElevatorMock1, call(_, _))
            .Times(0);

        EXPECT_CALL(*mElevatorMock2, getCurrentFloor())
            .Times(1)
            .WillOnce(Return(elevator::FloorNumber(2)));
        EXPECT_CALL(*mElevatorMock2, getCurrentStatus())
            .Times(1)
            .WillOnce(Return(elevator::ElevatorStatus::Wait));
        EXPECT_CALL(*mElevatorMock2, isFull())
            .Times(1)
            .WillOnce(Return(false));
        EXPECT_CALL(*mElevatorMock2, call(from, to))
            .Times(1)
            .WillOnce(Return(true));

        EXPECT_CALL(*mElevatorMock3, getCurrentFloor())
            .Times(1)
            .WillOnce(Return(elevator::FloorNumber(1)));
        EXPECT_CALL(*mElevatorMock3, getCurrentStatus())
            .Times(1)
            .WillOnce(Return(elevator::ElevatorStatus::Wait));
        EXPECT_CALL(*mElevatorMock3, isFull())
            .Times(1)
            .WillOnce(Return(false));
        EXPECT_CALL(*mElevatorMock3, call(_, _))
            .Times(0);

        elevatorsControl.callElevator(from, to, elevator::SelectDirection::Up);
    }

    TEST_F(ElevatorsControlFixture, testCallFromSecondIteration)
    {
        elevator::FloorNumber from = 5;
        elevator::FloorNumber to = 7;

        EXPECT_CALL(*mElevatorMock1, getCurrentFloor())
            .Times(2)
            .WillOnce(Return(elevator::FloorNumber(4)))
            .WillOnce(Return(elevator::FloorNumber(3)));
        EXPECT_CALL(*mElevatorMock1, getCurrentStatus())
            .Times(2)
            .WillOnce(Return(elevator::ElevatorStatus::MoveDown))
            .WillOnce(Return(elevator::ElevatorStatus::Wait));
        EXPECT_CALL(*mElevatorMock1, isFull())
            .Times(2)
            .WillRepeatedly(Return(false));
        EXPECT_CALL(*mElevatorMock1, call(from, to))
            .Times(1)
            .WillOnce(Return(true));

        EXPECT_CALL(*mElevatorMock2, getCurrentFloor())
            .Times(2)
            .WillOnce(Return(elevator::FloorNumber(6)))
            .WillOnce(Return(elevator::FloorNumber(7)));
        EXPECT_CALL(*mElevatorMock2, getCurrentStatus())
            .Times(2)
            .WillOnce(Return(elevator::ElevatorStatus::MoveUp))
            .WillOnce(Return(elevator::ElevatorStatus::MoveUp));
        EXPECT_CALL(*mElevatorMock2, isFull())
            .Times(2)
            .WillRepeatedly(Return(false));
        EXPECT_CALL(*mElevatorMock2, call(from, to))
            .Times(0);

        EXPECT_CALL(*mElevatorMock3, getCurrentFloor())
            .Times(2)
            .WillOnce(Return(elevator::FloorNumber(3)))
            .WillOnce(Return(elevator::FloorNumber(2)));
        EXPECT_CALL(*mElevatorMock3, getCurrentStatus())
            .Times(2)
            .WillOnce(Return(elevator::ElevatorStatus::MoveDown))
            .WillOnce(Return(elevator::ElevatorStatus::MoveDown));
        EXPECT_CALL(*mElevatorMock3, isFull())
            .Times(2)
            .WillRepeatedly(Return(false));
        EXPECT_CALL(*mElevatorMock3, call(_, _))
            .Times(0);

        elevatorsControl.callElevator(from, to, elevator::SelectDirection::Up);
    }
}
