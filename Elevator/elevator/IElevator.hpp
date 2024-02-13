
#ifndef IELEVATOR_H
#define IELEVATOR_H

#include <chrono>

#include "Types.hpp"

namespace elevator {
/**
 * @brief Contains elevator settings
 */
struct ElevatorParameter {
  ElevatorCapacity capacity;  /** < Elevator capacity */
  std::chrono::seconds speed; /** < Elevator speed (seconds per floor)*/
};

/**
 * @brief Status of elevator moving
 */
enum class ElevatorStatus {
  /** < Elevator is not moving and is waiting for a call */
  Wait,
  /** < Elevator is moving up */
  MoveUp,
  /** < Elevator is moving down */
  MoveDown,
  /** < Elevator moves but does not stop until it reaches the target
   * (between the call after waiting and reaching the floor from which the call was made) */
  MoveWithoutStop
};

/**
 * @brief Interface responsible for moving the elevator after a call
 */
class IElevator {
public:
  virtual ~IElevator() = default;

  /**
   * @brief Get the current elevator position (floor)
   *
   * @return floor number where the elevator is currently located
   */
  virtual FloorNumber getCurrentFloor() const = 0;

  /**
   * @brief Get the current elevator moving status
   *
   * @return elevator moving status
   */
  virtual ElevatorStatus getCurrentStatus() const = 0;

  /**
   * @brief Determines if the elevator is full or not
   *
   * @return true if the elevator is full, otherwise false
   */
  virtual bool isFull() const = 0;

  /**
   * @brief Performs an elevator call to the floor
   *
   * @param from - initial floor of the elevator call
   * @param to - target floor
   * @return true if the elevator can complete the current call, otherwise false
   */
  virtual bool call(FloorNumber from, FloorNumber to) = 0;
};

} // namespace elevator

#endif // IELEVATOR_H