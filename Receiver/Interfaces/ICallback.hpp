#pragma once

#include "Byte.hpp"

struct ICallback {
  ~ICallback() = default;

  virtual void binaryPacket(const Byte *data, std::size_t size) = 0;
  virtual void textPacket(const Byte *data, std::size_t size) = 0;
};