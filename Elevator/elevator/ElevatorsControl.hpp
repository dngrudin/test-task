#ifndef ELEVATOR_CONTROL_H
#define ELEVATOR_CONTROL_H

#include <memory>
#include <vector>

#include "IElevatorsControl.hpp"

namespace elevator {

class IElevator;

/**
 * @brief Implementation IElevatorsControl interface.
 */
class ElevatorsControl final : public IElevatorsControl {
  ElevatorsControl(const ElevatorsControl &) = delete;
  ElevatorsControl &operator=(const ElevatorsControl &) = delete;
  ElevatorsControl(ElevatorsControl &&) = delete;
  ElevatorsControl &operator=(ElevatorsControl &&) = delete;

public:
  ElevatorsControl() = default;
  ~ElevatorsControl();

  /**
   * @brief Enables elevators control for operation.
   *
   * @param elevators      - elevators list
   * @param callerToFloors - caller to floors list
   */
  void enable(std::vector<std::shared_ptr<IElevator>> &&elevators,
              std::vector<std::unique_ptr<ICallerToFloor>> &&callerToFloors) override;

  /**
   * @brief Disables elevators control for operation.
   */
  void disable() override;

  /**
   * @brief Makes an elevator call to the floor
   *
   * @param from      - initial floor of the elevator call
   * @param to        - target floor
   * @param direction - selected direction of movement of the elevator
   */
  void callElevator(FloorNumber from, FloorNumber to, CallDirection direction) override;

  /**
   * @brief Finds the call on the floor closest to the elevator if there is one
   *
   * @param elevatorFloor - floor regarding which the call is being sought
   * @return call information otherwise empty
   */
  std::optional<FindCallResult> findCall(FloorNumber elevatorFloor) const override;

  /**
   * @brief Executed when the elevator reaches the starting floor (if a direction is specified, then
   * it is checked that the call was in the same direction)
   *
   * @param floor - floor on which the elevator is currently located
   * @param direction - current elevator call direction
   * @return final floor if the call has not yet been processed, otherwise empty
   */
  std::optional<FloorNumber> doneCall(FloorNumber floor,
                                      std::optional<CallDirection> direction) const override;

private:
  std::vector<std::shared_ptr<IElevator>> mElevators;           /** < Elevators list */
  std::vector<std::unique_ptr<ICallerToFloor>> mCallerToFloors; /** < Callers to floor list */
};

} // namespace elevator

#endif // ELEVATOR_CONTROL_H