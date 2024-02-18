
#ifndef ELEVATOR_CONTROL_MOCK_H
#define ELEVATOR_CONTROL_MOCK_H

#include <gmock/gmock.h>

#include "IElevatorsControl.hpp"

namespace mock {

class ElevatorsControlMock final : public elevator::IElevatorsControl {
public:
  MOCK_METHOD(void, enable,
              (std::vector<std::shared_ptr<elevator::IElevator>> &&,
               std::vector<std::unique_ptr<elevator::ICallerToFloor>> &&),
              (override));
  MOCK_METHOD(void, disable, (), (override));
  MOCK_METHOD(void, callElevator,
              (elevator::FloorNumber, elevator::FloorNumber, elevator::CallDirection), (override));
  MOCK_METHOD(std::optional<elevator::FindCallResult>, findCall, (elevator::FloorNumber),
              (const, override));
  MOCK_METHOD(std::optional<elevator::FloorNumber>, doneCall,
              (elevator::FloorNumber, std::optional<elevator::CallDirection>), (const, override));
};

} // namespace mock

#endif // ELEVATOR_CONTROL_MOCK_H