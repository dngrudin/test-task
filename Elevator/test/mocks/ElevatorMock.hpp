
#ifndef ELEVATOR_MOCK_H
#define ELEVATOR_MOCK_H

#include <gmock/gmock.h>

#include "IElevator.hpp"

namespace mock {

class ElevatorMock final : public elevator::IElevator {
public:
  MOCK_METHOD(void, enable, (elevator::IElevatorsControl &), (override));
  MOCK_METHOD(void, disable, (), (override));
};

} // namespace mock

#endif // ELEVATOR_MOCK_H