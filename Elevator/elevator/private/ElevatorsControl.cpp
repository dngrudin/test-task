
#include "ElevatorsControl.hpp"

#include <optional>

#include "IElevator.hpp"

namespace elevator {

ElevatorsControl::~ElevatorsControl() { disable(); }

void ElevatorsControl::enable(std::vector<std::shared_ptr<IElevator>> &&elevators,
                              std::vector<std::unique_ptr<ICallerToFloor>> &&callerToFloors) {
  mCallerToFloors = std::move(callerToFloors);
  mElevators = std::move(elevators);
  for (auto &elevator : mElevators) {
    elevator->enable(*this);
  }
}

void ElevatorsControl::disable() {
  for (auto &elevator : mElevators) {
    elevator->disable();
  }
}

void ElevatorsControl::callElevator(FloorNumber from, FloorNumber to, CallDirection direction) {
  mCallerToFloors[from - 1]->call(direction, to);
}

std::optional<FindCallResult> ElevatorsControl::findCall(FloorNumber elevatorFloor) const {
  const auto checkCallerCall = [this](FloorNumber floor) {
    std::optional<FindCallResult> result;
    auto callStatus = mCallerToFloors[floor - 1]->checkCall();
    if (callStatus)
      result.emplace(floor, *callStatus);
    return result;
  };

  auto result = checkCallerCall(elevatorFloor);
  if (result)
    return result;

  std::int16_t offset = 1;

  // Looking for calls on the floors around the elevator
  // with a progressive increase in distance in both directions
  while (true) {
    if ((elevatorFloor - 1 + offset) < mCallerToFloors.size()) {
      if (result = checkCallerCall(elevatorFloor + offset); result) {
        break;
      }
    }

    if ((elevatorFloor - 1 - offset) >= 0) {
      if (result = checkCallerCall(elevatorFloor - offset); result) {
        break;
      }
    }

    if ((elevatorFloor - 1 + offset) >= mCallerToFloors.size() &&
        (elevatorFloor - 1 - offset) < 0) {
      break;
    }

    ++offset;
  }

  return result;
}

std::optional<FloorNumber>
ElevatorsControl::doneCall(FloorNumber floor, std::optional<CallDirection> direction) const {
  return mCallerToFloors[floor - 1]->doneCall(direction);
}

} // namespace elevator