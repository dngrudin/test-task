
#ifndef ICALLER_H
#define ICALLER_H

#include <optional>

#include "Types.hpp"

namespace elevator {

class ICallerToFloor {
public:
  virtual ~ICallerToFloor() = default;

  /**
   * @brief Makes an elevator call to the floor
   *
   * @param direction - selected direction of movement of the elevator
   * @param toFloorNumber - final floor
   */
  virtual void call(CallDirection direction, FloorNumber toFloorNumber) = 0;

  /**
   * @brief Checks if there is an active call to the floor
   *
   * @return call direction is it is otherwise empty
   */
  virtual std::optional<CallDirection> checkCall() = 0;

  /**
   * @brief Executed when the elevator reaches the starting floor (if a direction is specified, then
   * it is checked that the call was in the same direction)
   *
   * @param direction - current elevator call direction
   * @return final floor if the call has not yet been processed, otherwise empty
   */
  virtual std::optional<FloorNumber> doneCall(std::optional<CallDirection> direction) = 0;
};

} // namespace elevator

#endif // ICALLER_H