
#include <iterator>

#include "EventLogger.hpp"

namespace elevator {

void EventLogger::addEvent(ElevatorNumber elevator, FloorNumber floor, ElevatorFullness filled,
                           Event event) {
  const auto time = std::chrono::steady_clock::now();

  std::lock_guard lock(mEventMtx);
  mEvents.emplace_back(time, elevator, floor, filled, event);
}

void EventLogger::getEvents(std::vector<EventData> &events) const {
  events.clear();
  std::lock_guard lock(mEventMtx);
  events.reserve(mEvents.size());
  std::copy(std::begin(mEvents), std::end(mEvents), std::back_inserter(events));
}

void EventLogger::clearEvents() {
  std::lock_guard lock(mEventMtx);
  mEvents.clear();
}

} // namespace elevator
