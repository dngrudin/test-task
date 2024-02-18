
#include "testElevator.hpp"

using testing::_;
using testing::AtLeast;
using testing::Return;

namespace test {

void ElevatorFixture::SetUp() {
  const elevator::ElevatorParameter parameter{5, ElevatorSpeed, ElevatorAutoComebackAfter};

  mEventLoggerMock = std::make_shared<mock::EventLoggerMock>();
  mElevator = std::make_shared<elevator::Elevator>(1, parameter, mEventLoggerMock);
}

void ElevatorFixture::TearDown() {
  mElevator.reset();
  mEventLoggerMock.reset();
}

TEST_F(ElevatorFixture, testElevatorCall) {
  EXPECT_CALL(*mEventLoggerMock, addEvent(_, 1, _, elevator::Event::Up)).Times(AtLeast(1));
  EXPECT_CALL(*mEventLoggerMock, addEvent(_, 5, _, elevator::Event::Stop)).Times(AtLeast(1));
  EXPECT_CALL(*mEventLoggerMock, addEvent(_, 5, _, elevator::Event::Down)).Times(AtLeast(1));
  EXPECT_CALL(*mEventLoggerMock, addEvent(_, 1, _, elevator::Event::Stop)).Times(AtLeast(1));
  EXPECT_CALL(*mEventLoggerMock, clearEvents()).Times(0);

  EXPECT_CALL(mElevatorsControl, findCall(_))
      .WillOnce(Return(elevator::FindCallResult{5, elevator::CallDirection::Down}))
      .WillRepeatedly(Return(EmptyCallResult));

  EXPECT_CALL(mElevatorsControl, doneCall(_, _)).WillRepeatedly(Return(EmptyFloorNumber));

  EXPECT_CALL(mElevatorsControl, doneCall(5, _))
      .Times(AtLeast(1))
      .WillOnce(Return(elevator::FloorNumber{1}))
      .WillRepeatedly(Return(EmptyFloorNumber));

  mElevator->enable(mElevatorsControl);

  std::this_thread::sleep_for(40s);
}

TEST_F(ElevatorFixture, testPickUp) {
  EXPECT_CALL(*mEventLoggerMock, addEvent(_, 1, _, elevator::Event::Up)).Times(AtLeast(1));
  EXPECT_CALL(*mEventLoggerMock, addEvent(_, 5, _, elevator::Event::Stop)).Times(AtLeast(1));
  EXPECT_CALL(*mEventLoggerMock, addEvent(_, 5, _, elevator::Event::Down)).Times(AtLeast(1));
  EXPECT_CALL(*mEventLoggerMock, addEvent(_, 3, _, elevator::Event::Stop)).Times(AtLeast(1));
  EXPECT_CALL(*mEventLoggerMock, addEvent(_, 3, _, elevator::Event::Down)).Times(AtLeast(1));
  EXPECT_CALL(*mEventLoggerMock, addEvent(_, 2, _, elevator::Event::Stop)).Times(AtLeast(1));
  EXPECT_CALL(*mEventLoggerMock, addEvent(_, 2, _, elevator::Event::Down)).Times(AtLeast(1));
  EXPECT_CALL(*mEventLoggerMock, addEvent(_, 1, _, elevator::Event::Stop)).Times(AtLeast(1));
  EXPECT_CALL(*mEventLoggerMock, clearEvents()).Times(0);

  EXPECT_CALL(mElevatorsControl, findCall(_))
      .WillOnce(Return(elevator::FindCallResult{5, elevator::CallDirection::Down}))
      .WillRepeatedly(Return(EmptyCallResult));

  EXPECT_CALL(mElevatorsControl, doneCall(_, _)).WillRepeatedly(Return(EmptyFloorNumber));

  EXPECT_CALL(mElevatorsControl, doneCall(3, _))
      .Times(AtLeast(1))
      .WillOnce(Return(elevator::FloorNumber{2}))
      .WillRepeatedly(Return(EmptyFloorNumber));

  EXPECT_CALL(mElevatorsControl, doneCall(5, _))
      .Times(AtLeast(1))
      .WillOnce(Return(elevator::FloorNumber{1}))
      .WillRepeatedly(Return(EmptyFloorNumber));

  mElevator->enable(mElevatorsControl);

  std::this_thread::sleep_for(40s);
}

} // namespace test
