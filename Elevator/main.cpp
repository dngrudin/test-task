
#include <chrono>
#include <iostream>
#include <memory>
#include <vector>

#include "CallerToFloor.hpp"
#include "Elevator.hpp"
#include "ElevatorsControl.hpp"
#include "EventLogger.hpp"
#include "Types.hpp"

struct UserCall {
  std::chrono::seconds timeFromStart;
  elevator::FloorNumber from;
  elevator::FloorNumber to;
  elevator::CallDirection direction;
};

int main() {
  using namespace std::chrono_literals;

  static constexpr elevator::FloorNumber CountFloors = 10;

  const std::vector<elevator::ElevatorParameter> elevatorsParameter{
      {5, 2s, 5s}, {5, 2s, 5s}, {10, 3s, 5s}};

  const std::vector<UserCall> userCalls{
      {0s, 1, 5, elevator::CallDirection::Up},
      {10s, 3, 10, elevator::CallDirection::Up},
      {15s, 7, 1, elevator::CallDirection::Down},
  };

  std::chrono::steady_clock::time_point start;
  auto eventLogger = std::make_shared<elevator::EventLogger>();

  {
    elevator::ElevatorsControl evelvatorsControl{};

    std::vector<std::shared_ptr<elevator::IElevator>> elevators{};
    for (std::size_t i = 0; i < elevatorsParameter.size(); ++i) {
      auto elevator = std::make_shared<elevator::Elevator>(
          static_cast<elevator::ElevatorNumber>(i + 1), elevatorsParameter[i], eventLogger);
      elevators.emplace_back(std::move(elevator));
    }

    std::vector<std::unique_ptr<elevator::ICallerToFloor>> callerToFloors{};
    for (std::size_t i = 0; i < CountFloors; ++i) {
      auto callerToFloor =
          std::make_unique<elevator::CallerToFloor>(static_cast<elevator::FloorNumber>(i + 1));
      callerToFloors.emplace_back(std::move(callerToFloor));
    }

    evelvatorsControl.enable(std::move(elevators), std::move(callerToFloors));

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

  eventLogger->printEvents(start);

  return 0;
}
