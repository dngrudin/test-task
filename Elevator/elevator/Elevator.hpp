
#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <atomic>
#include <condition_variable>
#include <map>
#include <memory>
#include <thread>

#include "IElevator.hpp"
#include "Types.hpp"

namespace elevator {

class IEventLogger;

/**
 * @brief Implementation IElevator interface.
 */
class Elevator : public IElevator {
public:
  Elevator(ElevatorNumber number, ElevatorParameter parameter,
           std::shared_ptr<IEventLogger> logger);
  ~Elevator();

  Elevator(const Elevator &) = delete;
  Elevator &operator=(const Elevator &) = delete;
  Elevator(Elevator &&) = delete;
  Elevator &operator=(Elevator &&) = delete;

  /**
   * @brief Get the current elevator position (floor)
   *
   * @return floor number where the elevator is currently located
   */
  FloorNumber getCurrentFloor() const;

  /**
   * @brief Get the current elevator moving status
   *
   * @return elevator moving status
   */
  ElevatorStatus getCurrentStatus() const;

  /**
   * @brief Determines if the elevator is full or not
   *
   * @return true if the elevator is full, otherwise false
   */
  bool isFull() const;

  /**
   * @brief Performs an elevator call to the floor
   *
   * @param from - initial floor of the elevator call
   * @param to - target floor
   * @return true if the elevator can complete the current call, otherwise false
   */
  bool call(FloorNumber from, FloorNumber to);

private:
  /**
   * @brief Direction of movement of the elevator
   */
  enum class ElevatorDirection {
    Up,
    Down,
  };

  /**
   * @brief Target type
   */
  enum class Target {
    /** < Initial floor of the elevator call */
    From,
    /** < End floor */
    To,
  };

  /**
   * @brief Elevator call and stop queue (with the ability to choose the direction of calls)
   */
  using CallQueue = std::map<FloorNumber, Target>;

  /**
   * @brief Elevator call handler for a separate thread
   */
  void callsHandler();

  /**
   * @brief Get the target floor number
   *
   * @return target floor number
   */
  FloorNumber getTargetFloor() const;

  /**
   * @brief Performs a call dequeue when the target is reached
   */
  void reachTargetFloor();

  ElevatorDirection mDirection; /** < Direction of movement of the elevator */

  const ElevatorNumber mElevatorNumber;        /** < Elevator number */
  const ElevatorParameter mParameter;          /** < Elevator parameter */
  const std::shared_ptr<IEventLogger> mLogger; /** < Pointer to logger */

  CallQueue mCallQueue; /** < Elevator call and stop queue */

  std::atomic<FloorNumber>
      mCurrentFloor;                   /** < Floor number where the elevator is currently located */
  std::atomic<ElevatorStatus> mStatus; /** < Current elevator moving status */
  std::atomic<ElevatorCapacity> mFilled; /** < Elevator fullness */

  std::condition_variable mCallQueueCV;
  std::mutex mCallQueueMtx;
  std::thread mCallsHandlerThread;
  std::atomic<bool> isRun; /** < Sign that the elevator is processing calls */
};

} // namespace elevator

#endif // ELEVATOR_H