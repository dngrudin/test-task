#pragma once

#include <cstddef>

enum class PacketType { Undefined = 0, Binary, Text };

struct PacketState {
  PacketType type = PacketType::Undefined;
  std::size_t size = 0;
  std::size_t moveBack = 0;
};