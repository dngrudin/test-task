
#ifndef CALLER_TO_FLOOR_MOCK_H
#define CALLER_TO_FLOOR_MOCK_H

#include <gmock/gmock.h>

#include "ICallerToFloor.hpp"

namespace mock {

class CallerToFloorMock final : public elevator::ICallerToFloor {
public:
  MOCK_METHOD(void, call, (elevator::CallDirection direction, elevator::FloorNumber), (override));
  MOCK_METHOD(std::optional<elevator::CallDirection>, checkCall, (), (override));
  MOCK_METHOD(std::optional<elevator::FloorNumber>, doneCall,
              (std::optional<elevator::CallDirection>), (override));
};

} // namespace mock

#endif // CALLER_TO_FLOOR_MOCK_H