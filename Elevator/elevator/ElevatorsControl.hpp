#ifndef ELEVATOR_CONTROL_H
#define ELEVATOR_CONTROL_H

#include <memory>
#include <vector>

#include "IElevator.hpp"
#include "IElevatorsControl.hpp"

namespace elevator {

/**
 * @brief Implementation IElevatorsControl interface.
 */
class ElevatorsControl : public IElevatorsControl {
public:
  ElevatorsControl() = default;

  ElevatorsControl(const ElevatorsControl &) = delete;
  ElevatorsControl &operator=(const ElevatorsControl &) = delete;
  ElevatorsControl(ElevatorsControl &&) = delete;
  ElevatorsControl &operator=(ElevatorsControl &&) = delete;

  /**
   * @brief Sets elevators for operation.
   *
   * @param elevators - elevators list
   */
  void setElevators(std::vector<std::shared_ptr<IElevator>> elevators) override;

  /**
   * @brief Makes an elevator call to the floor
   *
   * @param from - initial floor of the elevator call
   * @param to - target floor
   * @param direction - selected direction of movement of the elevator
   */
  void callElevator(FloorNumber from, FloorNumber to, SelectDirection direction) override;

private:
  std::vector<std::shared_ptr<IElevator>> mElevators; /** < Elevators list */
};

} // namespace elevator

#endif // ELEVATOR_CONTROL_H