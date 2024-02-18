
#ifndef EVENT_LOG_H
#define EVENT_LOG_H

#include <list>
#include <memory>
#include <shared_mutex>

#include "IEventLogger.hpp"

namespace elevator {

/**
 * @brief Implementation IEventLogger interface.
 */
class EventLogger final : public IEventLogger {
  EventLogger(const EventLogger &) = delete;
  EventLogger &operator=(const EventLogger &) = delete;
  EventLogger(EventLogger &&) = delete;
  EventLogger &operator=(EventLogger &&) = delete;

public:
  EventLogger() = default;

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
   * @brief Print all events.
   *
   * @param baseTimepoint - time relative to which the time of events will be displayed
   */
  void printEvents(const EventData::Timepoint baseTimepoint) const override;

  /**
   * @brief Clear all events
   */
  void clearEvents() override;

private:
  std::list<EventData> mEvents;        /** < Event list */
  mutable std::shared_mutex mEventMtx; /** < Mutex to synchronize the list of events */
};

} // namespace elevator

#endif // EVENT_LOG_H