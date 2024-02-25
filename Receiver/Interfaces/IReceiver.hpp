#pragma once

#include "Byte.hpp"

struct IReceiver {
  ~IReceiver() = default;

  virtual void receive(const Byte *data, std::size_t size) = 0;
};