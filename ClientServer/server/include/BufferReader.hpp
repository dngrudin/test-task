
#ifndef BUFFER_READER_HPP
#define BUFFER_READER_HPP

#include "MD5.hpp"
#include "RingBuffer.hpp"
#include "Thread.hpp"

class BufferReader : public Thread {
public:
  BufferReader(RingBuffer &mRingBuffer);
  ~BufferReader();

private:
  bool checkMD5(unsigned char *data, std::size_t size);

  virtual void task();

  RingBuffer &mRingBuffer;
  RingBuffer::Cursor mLastCursor;
  MD5 mMD5;
};

#endif // BUFFER_READER_HPP