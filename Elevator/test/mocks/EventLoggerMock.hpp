
#ifndef EVENT_LOG_MOCK_H
#define EVENT_LOG_MOCK_H

#include <gmock/gmock.h>

#include "IEventLogger.hpp"

namespace mock
{
    class EventLoggerMock : public elevator::IEventLogger
    {
    public:
        MOCK_METHOD(void, addEvent, (elevator::ElevatorNumber, elevator::FloorNumber, elevator::ElevatorFullness, elevator::Event), (override));
        MOCK_METHOD(void, getEvents, (std::vector<elevator::EventData>&), (const, override));
        MOCK_METHOD(void, clearEvents, (), (override));
    };
}

#endif // EVENT_LOG_MOCK_H