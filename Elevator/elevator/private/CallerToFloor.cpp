
#include "CallerToFloor.hpp"

namespace elevator {

CallerToFloor::CallerToFloor(FloorNumber floorNumber) noexcept
    : mFloorNumber(floorNumber), mCallInfo{} {}

void CallerToFloor::call(CallDirection direction, FloorNumber toFloorNumber) {
  const CallInfo callChange{toFloorNumber, direction, false};

  CallInfo expected = CallInfo{};
  mCallInfo.compare_exchange_strong(expected, callChange);
}

std::optional<CallDirection> CallerToFloor::checkCall() {
  auto callInfo = mCallInfo.load(std::memory_order_relaxed);
  if (!callInfo.isElevatorSelected && (callInfo.callDirection != CallDirection::Invalid)) {
    const CallInfo callChange{callInfo.toFloor, callInfo.callDirection, true};
    if (mCallInfo.compare_exchange_strong(callInfo, callChange)) {
      return callInfo.callDirection;
    }
  }

  return {};
}

std::optional<FloorNumber> CallerToFloor::doneCall(std::optional<CallDirection> direction) {
  auto callInfo = mCallInfo.load(std::memory_order_relaxed);
  if ((callInfo.callDirection != CallDirection::Invalid) &&
      (!direction || (*direction == callInfo.callDirection))) {
    const CallInfo callChange{};
    if (mCallInfo.compare_exchange_strong(callInfo, callChange)) {
      return callInfo.toFloor;
    }
  }
  return {};
}

} // namespace elevator
