#pragma once

#include "Action.hpp"
#include "Byte.hpp"
#include "PacketState.hpp"
#include "PayloadRange.hpp"

namespace detail {

constexpr Byte BinaryStartByte = 0x24;

}

class TypeDetection {
public:
  TypeDetection(Action *actionForBinaryPacket, Action *actionForTextPacket,
                PacketState &packetState) noexcept
      : mActionForBinaryPacket(actionForBinaryPacket), mActionForTextPacket(actionForTextPacket),
        mPacketState(packetState) {}

  Action *operator()(const Byte *data, std::size_t size, std::size_t &offset,
                     PayloadRange &payloadRange) {
    if (*(data + offset) == detail::BinaryStartByte) {
      offset++;
      payloadRange.begin = offset;
      payloadRange.end = offset;
      mPacketState.type = PacketType::Binary;
      return mActionForBinaryPacket;
    }

    payloadRange.begin = offset;
    payloadRange.end = offset;
    mPacketState.type = PacketType::Text;
    return mActionForTextPacket;
  }

private:
  Action *mActionForBinaryPacket;
  Action *mActionForTextPacket;

  PacketState &mPacketState;
};