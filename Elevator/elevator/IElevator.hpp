
#ifndef IELEVATOR_H
#define IELEVATOR_H

#include <chrono>

#include "Types.hpp"

namespace elevator {

class IElevatorsControl;

using ElevatorCapacity = std::uint8_t;

/**
 * @brief Contains elevator settings
 */
struct ElevatorParameter {
  ElevatorCapacity capacity;              /** < Elevator capacity */
  std::chrono::seconds speed;             /** < Elevator speed (seconds per floor) */
  std::chrono::seconds autoComebackAfter; /** < Waiting time before comeback */
};

/**
 * @brief Interface responsible for moving the elevator after a call
 */
class IElevator {
public:
  virtual ~IElevator() = default;

  /**
   * @brief Enables elevator.
   *
   * @param elevatorsControl - elevators control
   */
  virtual void enable(IElevatorsControl &elevatorsControl) = 0;

  /**
   * @brief Disables elevator.
   */
  virtual void disable() = 0;
};

} // namespace elevator

#endif // IELEVATOR_H