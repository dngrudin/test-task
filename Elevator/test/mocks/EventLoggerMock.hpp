
#ifndef EVENT_LOGGER_MOCK_H
#define EVENT_LOGGER_MOCK_H

#include <gmock/gmock.h>

#include "IEventLogger.hpp"

namespace mock {

class EventLoggerMock final : public elevator::IEventLogger {
public:
  MOCK_METHOD(void, addEvent,
              (elevator::ElevatorNumber, elevator::FloorNumber, elevator::ElevatorFullness,
               elevator::Event),
              (override));
  MOCK_METHOD(void, printEvents, (const elevator::EventData::Timepoint), (const, override));
  MOCK_METHOD(void, clearEvents, (), (override));
};

} // namespace mock

#endif // EVENT_LOGGER_MOCK_H