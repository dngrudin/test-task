#ifndef IELEVATOR_CONTROL_H
#define IELEVATOR_CONTROL_H

#include <memory>
#include <vector>

#include "ICallerToFloor.hpp"
#include "Types.hpp"

namespace elevator {

class IElevator;

struct FindCallResult {
  FindCallResult(FloorNumber fromFloorNumber, CallDirection direction) noexcept
      : fromFloorNumber(fromFloorNumber), direction(direction) {}

  FloorNumber fromFloorNumber; /** < Floor on which the call was made */
  CallDirection direction;     /** < Call direction */
};

/**
 * @brief Interface responsible for managing elevator calls.
 */
class IElevatorsControl {
public:
  virtual ~IElevatorsControl() = default;

  /**
   * @brief Enables elevators control for operation.
   *
   * @param elevators      - elevators list
   * @param callerToFloors - caller to floors list
   */
  virtual void enable(std::vector<std::shared_ptr<IElevator>> &&elevators,
                      std::vector<std::unique_ptr<ICallerToFloor>> &&callerToFloors) = 0;

  /**
   * @brief Disables elevators control for operation.
   */
  virtual void disable() = 0;

  /**
   * @brief Makes an elevator call to the floor
   *
   * @param from      - initial floor of the elevator call
   * @param to        - target floor
   * @param direction - selected direction of movement of the elevator
   */
  virtual void callElevator(FloorNumber from, FloorNumber to, CallDirection direction) = 0;

  /**
   * @brief Finds the call on the floor closest to the elevator if there is one
   *
   * @param elevatorFloor - floor regarding which the call is being sought
   * @return call information otherwise empty
   */
  virtual std::optional<FindCallResult> findCall(FloorNumber elevatorFloor) const = 0;

  /**
   * @brief Executed when the elevator reaches the starting floor (if a direction is specified, then
   * it is checked that the call was in the same direction)
   *
   * @param floor - floor on which the elevator is currently located
   * @param direction - current elevator call direction
   * @return final floor if the call has not yet been processed, otherwise empty
   */
  virtual std::optional<FloorNumber> doneCall(FloorNumber floor,
                                              std::optional<CallDirection> direction) const = 0;
};

} // namespace elevator

#endif // IELEVATOR_CONTROL_H