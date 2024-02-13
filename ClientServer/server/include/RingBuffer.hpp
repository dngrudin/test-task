
#ifndef RING_BUFFER_HPP
#define RING_BUFFER_HPP

#include <cstddef>
#include <stdint.h>
#include <vector>

#include "ConditionVariable.hpp"
#include "Mutex.hpp"

class RingBuffer {
public:
  struct Cursor {
    Cursor(int32_t p, uint64_t l) : position(p), lap(l) {}

    bool operator==(const Cursor &other) const {
      return other.position == position && other.lap == lap;
    }

    bool operator!=(const Cursor &other) const { return !operator==(other); }

    int32_t position;
    uint64_t lap;
  };

  RingBuffer(std::size_t count, std::size_t bufferSize);
  ~RingBuffer();

  void write(unsigned char *data, std::size_t size);

  RingBuffer::Cursor getByCursorOrBack(RingBuffer::Cursor cursor,
                                       unsigned char *data, std::size_t &size);

  RingBuffer::Cursor waitForCursorChange(RingBuffer::Cursor cmpCursor);

  RingBuffer::Cursor getCursor() const;
  std::size_t getSize() const;
  std::size_t getBufferSize() const;

private:
  struct Buffer {
    unsigned char *data;
    std::size_t fillSize;
    Mutex mutex;
  };

  RingBuffer(const RingBuffer &);
  RingBuffer &operator=(const RingBuffer &);

  void init(std::size_t bufferSize);
  void clear();

  std::vector<Buffer> mBuffers;
  size_t mBufferSize;
  Cursor mCursor;
  mutable Mutex mCursorMutex;
  ConditionVariable mCursorCV;
};

#endif // RING_BUFFER_HPP