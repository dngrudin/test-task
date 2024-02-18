
#include "testElevatorsControl.hpp"

#include <memory>

using testing::_;
using testing::AtLeast;
using testing::Return;

namespace test {

void ElevatorsControlFixture::SetUp() {
  mElevatorMock1 = std::make_shared<mock::ElevatorMock>();
  mElevatorMock2 = std::make_shared<mock::ElevatorMock>();
  mElevatorMock3 = std::make_shared<mock::ElevatorMock>();

  mCallerToFloor1 = std::make_unique<mock::CallerToFloorMock>();
  mCallerToFloor2 = std::make_unique<mock::CallerToFloorMock>();
  mCallerToFloor3 = std::make_unique<mock::CallerToFloorMock>();
  mCallerToFloor4 = std::make_unique<mock::CallerToFloorMock>();
  mCallerToFloor5 = std::make_unique<mock::CallerToFloorMock>();

  EXPECT_CALL(*mElevatorMock1, enable(_)).Times(1);
  EXPECT_CALL(*mElevatorMock2, enable(_)).Times(1);
  EXPECT_CALL(*mElevatorMock3, enable(_)).Times(1);

  EXPECT_CALL(*mElevatorMock1, disable()).Times(AtLeast(1));
  EXPECT_CALL(*mElevatorMock2, disable()).Times(AtLeast(1));
  EXPECT_CALL(*mElevatorMock3, disable()).Times(AtLeast(1));
}

void ElevatorsControlFixture::TearDown() {
  mElevatorMock1.reset();
  mElevatorMock2.reset();
  mElevatorMock3.reset();

  elevatorsControl.disable();
}

TEST_F(ElevatorsControlFixture, testCall) {
  EXPECT_CALL(*mCallerToFloor4, call(elevator::CallDirection::Down, 1)).Times(1);

  std::vector<std::shared_ptr<elevator::IElevator>> elevators{mElevatorMock1, mElevatorMock2,
                                                              mElevatorMock3};
  std::vector<std::unique_ptr<elevator::ICallerToFloor>> callerToFloors;
  callerToFloors.emplace_back(std::move(mCallerToFloor1));
  callerToFloors.emplace_back(std::move(mCallerToFloor2));
  callerToFloors.emplace_back(std::move(mCallerToFloor3));
  callerToFloors.emplace_back(std::move(mCallerToFloor4));
  callerToFloors.emplace_back(std::move(mCallerToFloor5));
  elevatorsControl.enable(std::move(elevators), std::move(callerToFloors));

  elevatorsControl.callElevator(4, 1, elevator::CallDirection::Down);
}

TEST_F(ElevatorsControlFixture, testFind) {
  const elevator::FindCallResult checkCallResult =
      elevator::FindCallResult{4, elevator::CallDirection::Down};

  EXPECT_CALL(*mCallerToFloor2, checkCall()).Times(1).WillOnce(Return(EmptyCallDirection));
  EXPECT_CALL(*mCallerToFloor3, checkCall()).Times(1).WillOnce(Return(EmptyCallDirection));
  EXPECT_CALL(*mCallerToFloor1, checkCall()).Times(1).WillOnce(Return(EmptyCallDirection));
  EXPECT_CALL(*mCallerToFloor4, checkCall()).Times(1).WillOnce(Return(checkCallResult.direction));

  std::vector<std::shared_ptr<elevator::IElevator>> elevators{mElevatorMock1, mElevatorMock2,
                                                              mElevatorMock3};
  std::vector<std::unique_ptr<elevator::ICallerToFloor>> callerToFloors;
  callerToFloors.emplace_back(std::move(mCallerToFloor1));
  callerToFloors.emplace_back(std::move(mCallerToFloor2));
  callerToFloors.emplace_back(std::move(mCallerToFloor3));
  callerToFloors.emplace_back(std::move(mCallerToFloor4));
  callerToFloors.emplace_back(std::move(mCallerToFloor5));
  elevatorsControl.enable(std::move(elevators), std::move(callerToFloors));

  const auto findResult = elevatorsControl.findCall(2);
  EXPECT_TRUE(findResult);
  EXPECT_EQ((*findResult).direction, checkCallResult.direction);
  EXPECT_EQ((*findResult).fromFloorNumber, checkCallResult.fromFloorNumber);
}

TEST_F(ElevatorsControlFixture, testDoneCall) {
  const std::optional<elevator::FloorNumber> doneCallResult = elevator::FloorNumber{2};

  EXPECT_CALL(*mCallerToFloor3, doneCall(_)).Times(1).WillOnce(Return(EmptyFloorNumber));
  EXPECT_CALL(*mCallerToFloor2, doneCall(_)).Times(1).WillOnce(Return(doneCallResult));

  std::vector<std::shared_ptr<elevator::IElevator>> elevators{mElevatorMock1, mElevatorMock2,
                                                              mElevatorMock3};
  std::vector<std::unique_ptr<elevator::ICallerToFloor>> callerToFloors;
  callerToFloors.emplace_back(std::move(mCallerToFloor1));
  callerToFloors.emplace_back(std::move(mCallerToFloor2));
  callerToFloors.emplace_back(std::move(mCallerToFloor3));
  callerToFloors.emplace_back(std::move(mCallerToFloor4));
  callerToFloors.emplace_back(std::move(mCallerToFloor5));
  elevatorsControl.enable(std::move(elevators), std::move(callerToFloors));

  EXPECT_EQ(elevatorsControl.doneCall(3, {}), EmptyFloorNumber);
  EXPECT_EQ(elevatorsControl.doneCall(2, {}), doneCallResult);
}

} // namespace test
