
#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <atomic>
#include <memory>
#include <optional>
#include <thread>

#include "IElevator.hpp"
#include "Types.hpp"

namespace elevator {

class IEventLogger;

/**
 * @brief Implementation IElevator interface.
 */
class Elevator final : public IElevator {
  Elevator(const Elevator &) = delete;
  Elevator &operator=(const Elevator &) = delete;
  Elevator(Elevator &&) = delete;
  Elevator &operator=(Elevator &&) = delete;

public:
  Elevator(ElevatorNumber number, ElevatorParameter parameter,
           std::shared_ptr<IEventLogger> logger);
  ~Elevator();

  /**
   * @brief Enables elevator.
   *
   * @param elevatorsControl - elevators control
   */
  void enable(IElevatorsControl &elevatorsControl) override;

  /**
   * @brief Disables elevator.
   */
  void disable() override;

private:
  /**
   * @brief Elevator movement handler.
   *
   * @param elevatorsControl - elevators control
   */
  void moveHandler(IElevatorsControl &elevatorsControl);

  /**
   * @brief Moves the elevator to the specified floor.
   *
   * @param floorNumber - target floor
   * @param elevatorsControl - elevators control
   * @param changeFilling - indicates how much the elevator occupancy needs to be increased
   * @param pickUpDirection - if specified, it will check whether it is possible to pick up
   *                          passengers in the specified direction
   */
  void moveTo(FloorNumber floorNumber, IElevatorsControl &elevatorsControl,
              std::int8_t changeFilling = 0, std::optional<CallDirection> pickUpDirection = {});

  const std::shared_ptr<IEventLogger> mLogger; /** < Pointer to logger */

  const ElevatorNumber mElevatorNumber; /** < Elevator number */
  const ElevatorParameter mParameter;   /** < Elevator parameter */

  FloorNumber mCurrentFloor; /** < Floor number where the elevator is currently located */
  ElevatorCapacity mFilled;  /** < Elevator fullness */

  std::thread mMoveHandlerThread;
  std::atomic<bool> isRun; /** < Sign that the elevator is processing calls */
};

} // namespace elevator

#endif // ELEVATOR_H