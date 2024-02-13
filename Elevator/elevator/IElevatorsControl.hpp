#ifndef IELEVATOR_CONTROL_H
#define IELEVATOR_CONTROL_H

#include <vector>

#include "Elevator.hpp"
#include "Types.hpp"

namespace elevator {
/**
 * @brief Interface responsible for managing elevator calls.
 */
class IElevatorsControl {
public:
  virtual ~IElevatorsControl() = default;

  /**
   * @brief Sets elevators for operation.
   *
   * @param elevators - elevators list
   */
  virtual void setElevators(std::vector<std::shared_ptr<IElevator>> elevators) = 0;

  /**
   * @brief Makes an elevator call to the floor
   *
   * @param from - initial floor of the elevator call
   * @param to - target floor
   * @param direction - selected direction of movement of the elevator
   */
  virtual void callElevator(FloorNumber from, FloorNumber to, SelectDirection direction) = 0;
};

} // namespace elevator

#endif // IELEVATOR_CONTROL_H