
#include "IEventLogger.hpp"

#include "ElevatorsControl.hpp"

namespace elevator {

void ElevatorsControl::setElevators(std::vector<std::shared_ptr<IElevator>> elevators) {
  mElevators.clear();
  mElevators = std::move(elevators);
}

void ElevatorsControl::callElevator(FloorNumber from, FloorNumber to, SelectDirection direction) {
  if (!mElevators.empty()) {
    bool isCallDone = false;
    while (!isCallDone) {
      std::int32_t minDistance = -1;
      std::int32_t minDistanceElevator = -1;

      std::size_t index = 0;
      for (; index < mElevators.size(); ++index) {
        const auto &elevator = mElevators[index];
        if (!elevator->isFull()) /// filled elevators are ignored
        {
          const auto status = elevator->getCurrentStatus();
          const auto currentElevatorFloor = elevator->getCurrentFloor();

          std::int32_t distance = -1;

          /// finding the most suitable elevator
          if (status == ElevatorStatus::Wait) {
            distance = std::abs(from - currentElevatorFloor);
          } else if (direction == SelectDirection::Down && status == ElevatorStatus::MoveDown) {
            distance = currentElevatorFloor - from;
          } else if (direction == SelectDirection::Up && status == ElevatorStatus::MoveUp) {
            distance = from - currentElevatorFloor;
          }

          if ((distance >= 0) && ((distance < minDistance) || (minDistance < 0))) {
            minDistance = distance;
            minDistanceElevator = static_cast<std::int32_t>(index);
          }
        }
      }

      /// if an elevator is found, it is called
      isCallDone =
          (minDistanceElevator >= 0) ? mElevators[minDistanceElevator]->call(from, to) : false;
    }
  }
}

} // namespace elevator