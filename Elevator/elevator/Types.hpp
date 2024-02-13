
#ifndef TYPES_H
#define TYPES_H

#include <cstdint>

namespace elevator {

enum class SelectDirection { Up, Down };

using FloorNumber = std::int32_t;
using ElevatorNumber = std::uint8_t;
using ElevatorCapacity = std::uint8_t;
using ElevatorFullness = std::uint8_t;

} // namespace elevator

#endif // TYPES_H