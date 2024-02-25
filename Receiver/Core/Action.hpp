#pragma once

#include <functional>

#include "Byte.hpp"
#include "PayloadRange.hpp"

class Action;
using ActionHandler =
    std::function<Action *(const Byte *, std::size_t, std::size_t &, PayloadRange &)>;

class Action {
public:
  static constexpr Action *Continue = nullptr;

  Action(ActionHandler handler) : mHandler(std::move(handler)) {}

  Action *run(const Byte *data, std::size_t size, std::size_t &offset, PayloadRange &payloadRange) {
    return mHandler(data, size, offset, payloadRange);
  }

private:
  ActionHandler mHandler;
};
