#pragma once

#include <cstddef>
#include <cstring>

#include "Action.hpp"
#include "Byte.hpp"
#include "PacketState.hpp"
#include "PayloadRange.hpp"

class FindBinaryEnd {
public:
  FindBinaryEnd(Action *afterFindBinaryEnd, PacketState &packetState) noexcept
      : mAfterFindBinaryEnd(afterFindBinaryEnd), mPacketState(packetState) {}

  Action *operator()(const Byte *data, std::size_t size, std::size_t &offset,
                     PayloadRange &payloadRange) {
    const std::size_t countBytesToEnd = mPacketState.size - mRecievedSize;
    if (countBytesToEnd <= size - offset) {
      offset += countBytesToEnd;
      payloadRange.end = offset - 1;
      mRecievedSize = 0;
      return mAfterFindBinaryEnd;
    }

    payloadRange.end = size - 1;
    mRecievedSize += size - offset;
    offset = size;
    return Action::Continue;
  }

private:
  Action *mAfterFindBinaryEnd;

  std::size_t mRecievedSize = 0;

  PacketState &mPacketState;
};