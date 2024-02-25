#pragma once

#include <array>
#include <cstring>

#include "Action.hpp"
#include "Byte.hpp"
#include "PacketState.hpp"
#include "PayloadRange.hpp"

namespace detail {

constexpr std::size_t BinaryPacketSizeBytes = 4;

} // namespace detail

class BinarySizeParsing {
public:
  BinarySizeParsing(Action *afterSizeParsing, PacketState &packetState) noexcept
      : mAfterSizeParsing(afterSizeParsing), mPacketState(packetState) {}

  Action *operator()(const Byte *data, std::size_t size, std::size_t &offset,
                     PayloadRange &payloadRange) {
    const std::size_t countAddByteToSize =
        std::min(size - offset, detail::BinaryPacketSizeBytes - mFillSize);
    std::memcpy(mBinaryPacketSize.data() + mFillSize, data + offset, countAddByteToSize);

    mFillSize += countAddByteToSize;
    offset += countAddByteToSize;

    if (mFillSize == detail::BinaryPacketSizeBytes) {
      mFillSize = 0;
      payloadRange.begin = offset;
      payloadRange.end = offset;
      mPacketState.size = getSize();
      return mAfterSizeParsing;
    }

    return Action::Continue;
  }

private:
  static constexpr bool isSystemLittleEndian() {
    return static_cast<const Byte &>(std::uint32_t{1}) == 1;
  }

  std::uint32_t getSize() const noexcept {
    if (isSystemLittleEndian()) {
      return static_cast<std::uint32_t>(mBinaryPacketSize[3] << 24) | (mBinaryPacketSize[2] << 16) |
             (mBinaryPacketSize[1] << 8) | mBinaryPacketSize[0];
    } else {
      return static_cast<std::uint32_t>(mBinaryPacketSize[0] << 24) | (mBinaryPacketSize[1] << 16) |
             (mBinaryPacketSize[2] << 8) | mBinaryPacketSize[3];
    }
  }

  std::array<Byte, detail::BinaryPacketSizeBytes> mBinaryPacketSize;
  std::size_t mFillSize = 0;

  Action *mAfterSizeParsing;

  PacketState &mPacketState;
};