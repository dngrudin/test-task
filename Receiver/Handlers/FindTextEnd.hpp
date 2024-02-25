#pragma once

#include <array>
#include <cstddef>
#include <cstring>

#include "Action.hpp"
#include "Byte.hpp"
#include "PacketState.hpp"
#include "PayloadRange.hpp"

namespace detail {

constexpr std::array<Byte, 4> TextEnd{{'\r', '\n', '\r', '\n'}};

class PreviousBytes {
public:
  const Byte *getData() const { return (mSize > mPos) ? bytes.data() + mPos : nullptr; }

  std::size_t getSize() const { return (mSize > mPos) ? mSize - mPos : 0; }

  bool isEmpty() const { return mPos >= mSize; }

  bool shift() {
    mPos++;
    return !isEmpty();
  }

  void save(const Byte *data, std::size_t size) {
    mPos = 0;
    mSize = std::min(size, bytes.size());
    std::memcpy(bytes.data(), data, mSize);
  }

private:
  std::array<Byte, detail::TextEnd.size()> bytes{};
  std::size_t mPos = 0;
  std::size_t mSize = 0;
};

} // namespace detail

class FindTextEnd {
public:
  FindTextEnd(Action *afterFindTextEnd, PacketState &packetState) noexcept
      : mAfterFindTextEnd(afterFindTextEnd), mPacketState(packetState) {}

  Action *operator()(const Byte *data, std::size_t size, std::size_t &offset,
                     PayloadRange &payloadRange) {
    while (offset < size) {
      const std::size_t countCheckByte =
          std::min(size - offset, detail::TextEnd.size() - mCheckedPosistion);

      const bool isEqual =
          !std::memcmp(data + offset, detail::TextEnd.data() + mCheckedPosistion, countCheckByte);

      if (isEqual) {
        mPacketState.moveBack = mCheckedPosistion;

        offset += countCheckByte;
        mCheckedPosistion += countCheckByte;

        if (mCheckedPosistion == detail::TextEnd.size()) {
          mCheckedPosistion = 0;
          return mAfterFindTextEnd;
        } else {
          mPreviousBytes.save(data + offset - countCheckByte, countCheckByte);
          payloadRange.end = offset - 1;
          return Action::Continue;
        }
      }

      if (!mPreviousBytes.isEmpty()) {
        while (mPreviousBytes.shift()) {
          const bool isPreviousBytesEqual = !std::memcmp(
              mPreviousBytes.getData(), detail::TextEnd.data(), mPreviousBytes.getSize());
          if (isPreviousBytesEqual) {
            break;
          }
        }

        mCheckedPosistion = mPreviousBytes.getSize();
        if (mCheckedPosistion) {
          continue;
        }
      }

      mCheckedPosistion = 0;
      offset++;
      payloadRange.end = offset - 1;
    }

    return Action::Continue;
  }

private:
  Action *mAfterFindTextEnd;

  std::size_t mCheckedPosistion = 0;

  detail::PreviousBytes mPreviousBytes{};

  PacketState &mPacketState;
};