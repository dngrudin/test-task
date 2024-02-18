
#ifndef TEST_ELEVATOR_H
#define TEST_ELEVATOR_H

#include <memory>

#include <gtest/gtest.h>

#include "Elevator.hpp"
#include "IElevatorsControl.hpp"
#include "mocks/ElevatorsControlMock.hpp"
#include "mocks/EventLoggerMock.hpp"

using namespace std::chrono_literals;

namespace test {

class ElevatorFixture : public testing::Test {
public:
  void SetUp() override;

  void TearDown() override;

protected:
  static constexpr std::chrono::seconds ElevatorSpeed = 2s;
  static constexpr std::chrono::seconds ElevatorAutoComebackAfter = 5s;

  inline static const auto EmptyCallResult = std::optional<elevator::FindCallResult>{};
  inline static const auto EmptyFloorNumber = std::optional<elevator::FloorNumber>{};

  mock::ElevatorsControlMock mElevatorsControl;
  std::shared_ptr<mock::EventLoggerMock> mEventLoggerMock;
  std::shared_ptr<elevator::Elevator> mElevator;
};

} // namespace test

#endif // TEST_ELEVATOR_H
