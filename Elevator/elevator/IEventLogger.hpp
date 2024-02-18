
#ifndef IEVENT_LOG_H
#define IEVENT_LOG_H

#include <chrono>
#include <vector>

#include "Types.hpp"

namespace elevator {

enum class Event { Stop, Up, Down };

/**
 * @brief Event storage container.
 */
struct EventData {
  using Timepoint = std::chrono::steady_clock::time_point;

  EventData(Timepoint time, ElevatorNumber elevatorNumber, FloorNumber floorNumber,
            ElevatorFullness fullness, Event event) noexcept
      : time{time}, elevatorNumber{elevatorNumber},
        floorNumber{floorNumber}, fullness{fullness}, event{event} {}

  Timepoint time;
  ElevatorNumber elevatorNumber;
  FloorNumber floorNumber;
  ElevatorFullness fullness;
  Event event;
};

/**
 * @brief Interface responsible for collecting events about changing the status of elevators.
 */
class IEventLogger {
public:
  virtual ~IEventLogger() = default;

  /**
   * @brief Responsible for collecting events about changing the status of elevators.
   *
   * @param elevator - elevator number
   * @param floor    - floor number
   * @param fullness - elevator fullness
   * @param event    - event type
   */
  virtual void addEvent(ElevatorNumber elevator, FloorNumber floor, ElevatorFullness fullness,
                        Event event) = 0;

  /**
   * @brief Print all events.
   *
   * @param baseTimepoint - time relative to which the time of events will be displayed
   */
  virtual void printEvents(const EventData::Timepoint baseTimepoint) const = 0;

  /**
   * @brief Clear all events
   */
  virtual void clearEvents() = 0;
};

} // namespace elevator

#endif // IEVENT_LOG_H