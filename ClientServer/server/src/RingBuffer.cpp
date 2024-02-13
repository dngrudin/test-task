
#include <algorithm>
#include <string.h>

#include "RingBuffer.hpp"

namespace {

template <typename T> class NotEqualValuesPredicate {
public:
  NotEqualValuesPredicate(const T &inputValue, T baseValue)
      : mInputValue(inputValue), mBaseValue(baseValue) {}

  bool operator()() const { return mInputValue != mBaseValue; }

private:
  const T &mInputValue;
  T mBaseValue;
};

} // namespace

RingBuffer::RingBuffer(std::size_t count, std::size_t bufferSize)
    : mBuffers(count), mBufferSize(bufferSize), mCursor(-1, 0) {
  init(mBufferSize);
}

RingBuffer::~RingBuffer() { clear(); }

RingBuffer::Cursor RingBuffer::getCursor() const {
  Cursor cursor(-1, 0);

  {
    MutexLocker locker(mCursorMutex);
    cursor = mCursor;
  }

  return cursor;
}

std::size_t RingBuffer::getSize() const { return mBuffers.size(); }

std::size_t RingBuffer::getBufferSize() const { return mBufferSize; }

RingBuffer::Cursor
RingBuffer::waitForCursorChange(RingBuffer::Cursor cmpCursor) {
  MutexLocker locker(mCursorMutex);
  if (mCursor == cmpCursor) {
    mCursorCV.wait(mCursorMutex, NotEqualValuesPredicate<RingBuffer::Cursor>(
                                     mCursor, cmpCursor));
  }

  return mCursor;
}

void RingBuffer::write(unsigned char *data, std::size_t size) {
  if (size <= mBufferSize) {
    {
      MutexLocker locker(mCursorMutex);
      mCursor.position++;
      if (mCursor.position >= mBuffers.size()) {
        mCursor.lap++;
        mCursor.position = 0;
      };
    }

    Buffer &buffer = mBuffers[mCursor.position];

    {
      MutexLocker locker(buffer.mutex);
      memcpy(buffer.data, data, size);
      buffer.fillSize = size;
    }

    mCursorCV.notify();
  }
}

RingBuffer::Cursor RingBuffer::getByCursorOrBack(RingBuffer::Cursor cursor,
                                                 unsigned char *data,
                                                 std::size_t &size) {
  MutexLocker locker(mCursorMutex);

  if (((cursor.position <= mCursor.position) && (cursor.lap < mCursor.lap)) ||
      (cursor.lap + 1 < mCursor.lap)) {
    /// if the write has overtaken the read
    cursor = mCursor;

    if (cursor.position + 1 == mBuffers.size()) {
      cursor.position = 0;
    } else {
      cursor.lap--;
      cursor.position++;
      if (cursor.position >= mBuffers.size()) {
        cursor.position = 0;
      };
    }
  }

  if (cursor.position >= 0) {
    Buffer &buffer = mBuffers[cursor.position];

    MutexLocker locker(buffer.mutex);
    size = std::min(size, buffer.fillSize);
    memcpy(data, buffer.data, size);
  }

  return cursor;
}

void RingBuffer::init(std::size_t bufferSize) {
  for (std::size_t i = 0; i < mBuffers.size(); ++i) {
    Buffer &buffer = mBuffers[i];
    buffer.data = new unsigned char[bufferSize];
    buffer.fillSize = 0;
  }
}

void RingBuffer::clear() {
  for (std::size_t i = 0; i < mBuffers.size(); ++i) {
    Buffer &buffer = mBuffers[i];
    delete[] buffer.data;
  }
}
