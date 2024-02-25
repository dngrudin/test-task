#pragma once

#include "Action.hpp"
#include "Byte.hpp"
#include "PayloadRange.hpp"

class PakageComplete {
public:
  Action *operator()(const Byte *data, std::size_t size, std::size_t &offset,
                     PayloadRange &payloadRange) {
    return Action::Continue;
  }
};