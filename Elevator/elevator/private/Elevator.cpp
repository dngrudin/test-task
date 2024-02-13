
#include "IEventLogger.hpp"

#include "Elevator.hpp"

namespace elevator {

Elevator::Elevator(ElevatorNumber number, ElevatorParameter parametr,
                   std::shared_ptr<IEventLogger> logger)
    : mElevatorNumber(number), mParameter(std::move(parametr)), mLogger(std::move(logger)),
      mCurrentFloor(1), mStatus(ElevatorStatus::Wait),
      mCallsHandlerThread(&Elevator::callsHandler, this), isRun(true) {}

Elevator::~Elevator() {
  isRun.store(false, std::memory_order_release);
  mCallQueueCV.notify_all();
  mCallsHandlerThread.join();
}

FloorNumber Elevator::getCurrentFloor() const {
  return mCurrentFloor.load(std::memory_order_acquire);
}

ElevatorStatus Elevator::getCurrentStatus() const {
  return mStatus.load(std::memory_order_acquire);
}

bool Elevator::isFull() const {
  const auto filled = mFilled.load(std::memory_order_acquire);
  return filled >= mParameter.capacity;
}

bool Elevator::call(FloorNumber from, FloorNumber to) {
  bool isCallAvalible = true;
  {
    std::unique_lock lock(mCallQueueMtx);
    if (mCallQueue.empty()) {
      /// state update if the elevator has not moved before
      mDirection = to > from ? ElevatorDirection::Up : ElevatorDirection::Down;
      mStatus.store(ElevatorStatus::MoveWithoutStop, std::memory_order_relaxed);
    } else if ((mStatus == ElevatorStatus::MoveWithoutStop) ||
               ((mDirection == ElevatorDirection::Up) && (mCurrentFloor > from)) ||
               ((mDirection == ElevatorDirection::Down) && (mCurrentFloor < from))) {
      isCallAvalible = false;
    }

    /// if the elevator has the ability to stop at the specified floors, then the call is added to
    /// the queue
    if (isCallAvalible) {
      mCallQueue.emplace(from, Target::From);
      mCallQueue.emplace(to, Target::To);
    }
  }
  mCallQueueCV.notify_all();

  return isCallAvalible;
}

void Elevator::callsHandler() {
  while (isRun.load(std::memory_order_acquire)) {
    FloorNumber targetFloor{};
    FloorNumber currentFloor{};

    {
      std::unique_lock lock(mCallQueueMtx);

      if (mCallQueue.empty()) {
        /// waiting for a new call
        mStatus.store(ElevatorStatus::Wait, std::memory_order_relaxed);
        mCallQueueCV.wait(lock, [this]() {
          return !mCallQueue.empty() || !isRun.load(std::memory_order_acquire);
        });
      }

      if (!isRun.load(std::memory_order_relaxed)) {
        break;
      }

      targetFloor = getTargetFloor();
      currentFloor = mCurrentFloor.load(std::memory_order_relaxed);
      if (currentFloor == targetFloor) {
        /// if the elevator is already on the desired floor, then proceed to processing the next
        /// target floor
        reachTargetFloor();
        continue;
      }
    }

    const auto movingStartTime = std::chrono::steady_clock::now();
    mLogger->addEvent(mElevatorNumber, currentFloor, mFilled.load(std::memory_order_relaxed),
                      (currentFloor < targetFloor ? Event::Up : Event::Down));

    /// move the elevator to the nearest target floor
    bool isReachTargetFloor = false;
    for (std::uint32_t iteration = 1; !isReachTargetFloor; ++iteration) {
      /// waiting for the elevator to move between floors
      std::this_thread::sleep_until(movingStartTime + iteration * mParameter.speed);

      /// change the floor depending on the direction of movement
      mCurrentFloor.fetch_add((currentFloor < targetFloor) ? 1 : -1, std::memory_order_release);
      currentFloor = mCurrentFloor.load(std::memory_order_relaxed);

      {
        std::unique_lock lock(mCallQueueMtx);
        targetFloor = getTargetFloor();
        /// check if the nearest target floor has changed during the movement
        if (currentFloor == targetFloor) {
          /// if the elevator is already on the desired floor, then proceed to processing the next
          /// target floor
          reachTargetFloor();
          isReachTargetFloor = true;
        }
      }
    }

    mLogger->addEvent(mElevatorNumber, currentFloor, mFilled.load(std::memory_order_relaxed),
                      Event::Stop);
  }
}

FloorNumber Elevator::getTargetFloor() const {
  FloorNumber targetFloor = 1;
  if (!mCallQueue.empty()) {
    /// the nearest target floor is selected based on the direction of the elevator
    targetFloor = (mDirection == ElevatorDirection::Up) ? mCallQueue.cbegin()->first
                                                        : mCallQueue.crbegin()->first;
  }
  return targetFloor;
}

void Elevator::reachTargetFloor() {
  if (!mCallQueue.empty()) {
    CallQueue::iterator toErase{};
    if (mDirection == ElevatorDirection::Up) {
      toErase = mCallQueue.begin();
    } else {
      toErase = mCallQueue.end();
      --toErase;
    }

    /// updating information about the current fullness of the elevator
    mFilled.fetch_add((toErase->second == Target::From) ? 1 : -1, std::memory_order_relaxed);

    /// remove the target floor from the queue
    mCallQueue.erase(toErase);
  }

  /// update the status of the movement of the elevator
  mStatus.store((mDirection == ElevatorDirection::Up) ? ElevatorStatus::MoveUp
                                                      : ElevatorStatus::MoveDown,
                std::memory_order_relaxed);
}

} // namespace elevator