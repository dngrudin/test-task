
#include <chrono>
#include <iostream>
#include <vector>

#include "Elevator.hpp"
#include "ElevatorsControl.hpp"
#include "EventLogger.hpp"

struct UserCall {
  std::chrono::seconds timeFromStart;
  elevator::FloorNumber from;
  elevator::FloorNumber to;
  elevator::SelectDirection direction;
};

void printEvents(const std::vector<elevator::EventData> &events,
                 const std::chrono::steady_clock::time_point &baseTimepoint);

int main() {
  using namespace std::chrono_literals;

  const std::vector<elevator::ElevatorParameter> elevatorsParameter{{5, 2s}, {5, 2s}, {10, 3s}};

  const std::vector<UserCall> userCalls{
      {0s, 1, 5, elevator::SelectDirection::Up},
      {10s, 3, 10, elevator::SelectDirection::Up},
      {15s, 7, 1, elevator::SelectDirection::Down},
  };

  std::chrono::steady_clock::time_point start;
  auto eventLogger = std::make_shared<elevator::EventLogger>();

  {
    elevator::ElevatorsControl evelvatorsControl{};

    std::vector<std::shared_ptr<elevator::IElevator>> elevators{};
    for (std::size_t index = 0; index < elevatorsParameter.size(); ++index) {
      auto elevator = std::make_shared<elevator::Elevator>(
          static_cast<elevator::ElevatorNumber>(index + 1), elevatorsParameter[index], eventLogger);
      elevators.emplace_back(std::move(elevator));
    }
    evelvatorsControl.setElevators(elevators);

    std::cout << "Start\n";

    start = std::chrono::steady_clock::now();
    for (const auto &userCall : userCalls) {
      std::this_thread::sleep_until(start + userCall.timeFromStart);
      evelvatorsControl.callElevator(userCall.from, userCall.to, userCall.direction);
    }

    std::cout << "Wait\n";
    std::this_thread::sleep_until(start + 40s);
    std::cout << "Stop\n";
  }

  std::vector<elevator::EventData> events{};
  eventLogger->getEvents(events);

  std::cout << "Print log\n";
  printEvents(events, start);

  return 0;
}

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

void printEvents(const std::vector<elevator::EventData> &events,
                 const std::chrono::steady_clock::time_point &baseTimepoint) {
  for (const auto &event : events) {
    std::cout << std::chrono::duration<double>(event.time - baseTimepoint).count() << ' '
              << static_cast<std::int32_t>(event.elevatorNumber) << ' ' << event.floorNumber << ' '
              << eventToString(event.event) << ' ' << static_cast<std::int32_t>(event.fullness)
              << '\n';
  }
}
