#pragma once

#include <cstring>
#include <memory>

#include "Byte.hpp"

constexpr std::size_t DefaultBlockSize = 100 * 1024 * 1024; // 100 MB

class Buffer {
public:
  Buffer(std::size_t countBlocks = 2, std::size_t blockSize = DefaultBlockSize);

  Byte *getData() const { return mData.get(); }

  std::size_t getSize() const noexcept { return mSize; }

  std::size_t getCapacity() const noexcept { return mCountBlocks * mBlockSize; }

  void extend(std::size_t countBlocks);

  void append(const Byte *data, std::size_t size);

  void moveBack(std::size_t size);

  void reset() { mSize = 0; }

private:
  using Data = std::unique_ptr<Byte[]>;

  Byte *allocate(std::size_t countBlocks) const;

  Data mData;

  std::size_t mSize = 0;
  std::size_t mCountBlocks;
  const std::size_t mBlockSize;
};

inline Buffer::Buffer(std::size_t countBlocks, std::size_t blockSize)
    : mCountBlocks(countBlocks), mBlockSize(blockSize) {
  mData.reset(allocate(mCountBlocks));
  std::memset(mData.get(), 0x00, getCapacity());
}

inline void Buffer::extend(std::size_t countBlocks) {
  Byte *data = allocate(mCountBlocks + countBlocks);
  std::memcpy(data, mData.get(), getSize());
  mData.reset(data);
  mCountBlocks += countBlocks;
}

inline Byte *Buffer::allocate(std::size_t countBlocks) const {
  return new Byte[countBlocks * mBlockSize];
}

inline void Buffer::append(const Byte *data, std::size_t size) {
  if (getSize() + size >= getCapacity()) {
    const std::size_t addBloacks = 1 + ((getSize() + size) - getCapacity()) / mBlockSize;
    extend(addBloacks);
  }
  std::memcpy(mData.get() + mSize, data, size);
  mSize += size;
}

inline void Buffer::moveBack(std::size_t size) {
  if (mSize > size) {
    mSize -= size;
  } else {
    mSize = 0;
  }
}