
#include <chrono>
#include <iomanip>
#include <iostream>
#include <mutex>

#include "EventLogger.hpp"

namespace {

inline const char *eventToString(elevator::Event event) {
  switch (event) {
  case elevator::Event::Stop:
    return "Stop";
  case elevator::Event::Up:
    return "Up";
  case elevator::Event::Down:
    return "Down";
  }

  return "";
}

} // namespace

namespace elevator {

void EventLogger::addEvent(ElevatorNumber elevator, FloorNumber floor, ElevatorFullness filled,
                           Event event) {
  const auto time = std::chrono::steady_clock::now();

  std::unique_lock lock(mEventMtx);
  mEvents.emplace_back(time, elevator, floor, filled, event);
}

void EventLogger::clearEvents() {
  std::unique_lock lock(mEventMtx);
  mEvents.clear();
}

void EventLogger::printEvents(const EventData::Timepoint baseTimepoint) const {
  std::cout << "Print log:\n";
  std::shared_lock lock(mEventMtx);
  for (const auto &event : mEvents) {
    const auto duration = event.time - baseTimepoint;

    std::cout << std::setw(2) << std::setfill('0')
              << std::chrono::duration_cast<std::chrono::minutes>(duration).count() << ':'
              << std::setw(2) << std::setfill('0')
              << std::chrono::duration_cast<std::chrono::seconds>(duration).count() << '\t'
              << static_cast<std::int32_t>(event.elevatorNumber) << '\t' << event.floorNumber
              << '\t' << eventToString(event.event) << '\t'
              << static_cast<std::int32_t>(event.fullness) << '\n';
  }
}

} // namespace elevator
