
#ifndef CALLER_H
#define CALLER_H

#include "ICallerToFloor.hpp"

#include <atomic>

namespace elevator {

/**
 * @brief Implementation ICallerToFloor interface.
 */
class CallerToFloor final : public ICallerToFloor {
public:
  CallerToFloor(FloorNumber floorNumber) noexcept;

  /**
   * @brief Makes an elevator call to the floor
   *
   * @param direction - selected direction of movement of the elevator
   * @param toFloorNumber - final floor
   */
  void call(CallDirection direction, FloorNumber toFloorNumber) override;

  /**
   * @brief Checks if there is an active call to the floor
   *
   * @return call direction is it is otherwise empty
   */
  std::optional<CallDirection> checkCall() override;

  /**
   * @brief Executed when the elevator reaches the starting floor (if a direction is specified, then
   * it is checked that the call was in the same direction)
   *
   * @param direction - current elevator call direction
   * @return final floor if the call has not yet been processed, otherwise empty
   */
  std::optional<FloorNumber> doneCall(std::optional<CallDirection> direction) override;

private:
  const FloorNumber mFloorNumber; /** < Floor on which the calling mechanism is located*/

  /**
   * @brief Current call information.
   */
  struct CallInfo {
    FloorNumber toFloor = 0;                              /** < Final floor */
    CallDirection callDirection = CallDirection::Invalid; /** < Elevator call direction */
    bool isElevatorSelected =
        false; /** < Sign that some elevator has started servicing this call */
  };

  static_assert(std::atomic<CallInfo>::is_always_lock_free);

  std::atomic<CallInfo> mCallInfo;
};

} // namespace elevator

#endif // CALLER_H