
#ifndef TYPES_H
#define TYPES_H

#include <cstdint>

namespace elevator {

enum class CallDirection : std::int8_t { Invalid = 0, Up = 1, Down = 2 };

using ElevatorNumber = std::uint8_t;
using FloorNumber = std::uint16_t;
using ElevatorFullness = std::uint8_t;

} // namespace elevator

#endif // TYPES_H