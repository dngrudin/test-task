
#include "Elevator.hpp"

#include <queue>

#include "IElevatorsControl.hpp"
#include "IEventLogger.hpp"

namespace elevator {

Elevator::Elevator(ElevatorNumber number, ElevatorParameter parametr,
                   std::shared_ptr<IEventLogger> logger)
    : mLogger(std::move(logger)), mElevatorNumber(number), mParameter(parametr), mCurrentFloor(1),
      isRun(false) {}

Elevator::~Elevator() { disable(); }

void Elevator::enable(IElevatorsControl &elevatorsControl) {
  bool expected = false;
  if (isRun.compare_exchange_strong(expected, true, std::memory_order_release,
                                    std::memory_order_relaxed)) {
    mMoveHandlerThread = std::thread([this, &elevatorsControl] { moveHandler(elevatorsControl); });
  }
}

void Elevator::disable() {
  bool expected = true;
  if (isRun.compare_exchange_strong(expected, false, std::memory_order_release,
                                    std::memory_order_relaxed)) {
    mMoveHandlerThread.join();
  }
}

void Elevator::moveHandler(IElevatorsControl &elevatorsControl) {
  using namespace std::chrono_literals;

  auto startedCallWaiting = std::chrono::steady_clock::now();
  while (isRun.load(std::memory_order_acquire)) {
    if (const auto callResult = elevatorsControl.findCall(mCurrentFloor); callResult) {
      // If there is a call, move to the desired floor
      moveTo(callResult->fromFloorNumber, elevatorsControl);
      if (const auto toFloorNumber = elevatorsControl.doneCall(callResult->fromFloorNumber, {});
          toFloorNumber) {
        // If the call has not yet been serviced, then execute it
        moveTo(*toFloorNumber, elevatorsControl, 1, callResult->direction);
        mFilled = 0;
      }
      startedCallWaiting = std::chrono::steady_clock::now();
    } else if (mCurrentFloor > 1 && (std::chrono::steady_clock::now() - startedCallWaiting >=
                                     mParameter.autoComebackAfter)) {
      // Comeback the elevator to the first floor after autoComebackAfter seconds of inactivity
      moveTo(1, elevatorsControl);
    } else {
      std::this_thread::sleep_for(100ms);
    }
  }
}

void Elevator::moveTo(FloorNumber floorNumber, IElevatorsControl &elevatorsControl,
                      std::int8_t changeFilling, std::optional<CallDirection> pickUpDirection) {
  if (floorNumber != mCurrentFloor) {
    std::priority_queue<FloorNumber> targetFloorNumbers;
    targetFloorNumbers.push(floorNumber);

    while (!targetFloorNumbers.empty()) {
      const auto targetFloorNumber = targetFloorNumbers.top();

      mFilled += changeFilling;

      const auto movingStartTime = std::chrono::steady_clock::now();
      mLogger->addEvent(mElevatorNumber, mCurrentFloor, mFilled,
                        (mCurrentFloor < targetFloorNumber ? Event::Up : Event::Down));

      std::uint16_t iteration = 1;
      while (true) {
        /// Waiting for the elevator to move between floors
        std::this_thread::sleep_until(movingStartTime + iteration * mParameter.speed);

        /// Change the floor depending on the direction of movement
        mCurrentFloor += (mCurrentFloor < targetFloorNumber) ? 1 : -1;

        if (mCurrentFloor == targetFloorNumber) {
          changeFilling = 0;
          while (!targetFloorNumbers.empty() && targetFloorNumber == targetFloorNumbers.top()) {
            targetFloorNumbers.pop();
            changeFilling += -1;
          }
          break;
        }

        if (pickUpDirection && (mFilled <= mParameter.capacity)) {
          const auto toFloorNumber = elevatorsControl.doneCall(mCurrentFloor, pickUpDirection);
          if (toFloorNumber) {
            targetFloorNumbers.push(*toFloorNumber);
            changeFilling = 1;
            break;
          }
        }

        ++iteration;
      }

      mLogger->addEvent(mElevatorNumber, mCurrentFloor, mFilled, Event::Stop);
    }
  }
}

} // namespace elevator