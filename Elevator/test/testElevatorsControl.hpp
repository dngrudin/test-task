
#ifndef TEST_ELEVATOR_CONTROL_H
#define TEST_ELEVATOR_CONTROL_H

#include <memory>

#include <gtest/gtest.h>

#include "ElevatorsControl.hpp"
#include "mocks/CallerToFloorMock.hpp"
#include "mocks/ElevatorMock.hpp"

namespace test {

class ElevatorsControlFixture : public testing::Test {
public:
  void SetUp() override;

  void TearDown() override;

protected:
  inline static const auto EmptyCallDirection = std::optional<elevator::CallDirection>{};
  inline static const auto EmptyFloorNumber = std::optional<elevator::FloorNumber>{};

  std::shared_ptr<mock::ElevatorMock> mElevatorMock1;
  std::shared_ptr<mock::ElevatorMock> mElevatorMock2;
  std::shared_ptr<mock::ElevatorMock> mElevatorMock3;

  std::unique_ptr<mock::CallerToFloorMock> mCallerToFloor1;
  std::unique_ptr<mock::CallerToFloorMock> mCallerToFloor2;
  std::unique_ptr<mock::CallerToFloorMock> mCallerToFloor3;
  std::unique_ptr<mock::CallerToFloorMock> mCallerToFloor4;
  std::unique_ptr<mock::CallerToFloorMock> mCallerToFloor5;

  elevator::ElevatorsControl elevatorsControl;
};

} // namespace test

#endif // TEST_ELEVATOR_CONTROL_H
