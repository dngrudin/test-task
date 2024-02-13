
#ifndef EVENT_LOG_H
#define EVENT_LOG_H

#include <list>
#include <mutex>

#include "IEventLogger.hpp"

namespace elevator {

/**
 * @brief Implementation IEventLogger interface.
 */
class EventLogger : public IEventLogger {
public:
  EventLogger() = default;

  EventLogger(const EventLogger &) = delete;
  EventLogger &operator=(const EventLogger &) = delete;
  EventLogger(EventLogger &&) = delete;
  EventLogger &operator=(EventLogger &&) = delete;

  /**
   * @brief Responsible for collecting events about changing the status of elevators.
   *
   * @param elevator - elevator number
   * @param floor - floor number
   * @param fullness - elevator fullness
   * @param event - event type
   */
  void addEvent(ElevatorNumber elevator, FloorNumber floor, ElevatorFullness fullness,
                Event event) override;

  /**
   * @brief Get the event list
   *
   * @param events - list of events that have occurred
   */
  void getEvents(std::vector<EventData> &events) const override;

  /**
   * @brief Clear all events
   */
  void clearEvents() override;

private:
  std::list<EventData> mEvents; /** < Event list */
  mutable std::mutex mEventMtx; /** < Mutex to synchronize the list of events */
};

} // namespace elevator

#endif // EVENT_LOG_H