
#include <iostream>
#include <string.h>

#include "BufferReader.hpp"
#include "Constants.hpp"
#include "DataConverter.hpp"
#include "Time.hpp"

#define PROCESSING_TIME_MICROSECONDS (15 * 1000)

BufferReader::BufferReader(RingBuffer &ringBuffer)
    : mRingBuffer(ringBuffer), mLastCursor(-1, 0), mMD5() {}

BufferReader::~BufferReader() {}

void BufferReader::task() {
  unsigned char *buffer = new unsigned char[BUFFER_BYTES];

  const std::size_t ringBufferSize = mRingBuffer.getSize();
  while (true) {
    RingBuffer::Cursor cursor = mRingBuffer.waitForCursorChange(mLastCursor);
    if (mLastCursor != cursor) {
      mLastCursor.position++;
      if (mLastCursor.position == ringBufferSize) {
        mLastCursor.lap++;
        mLastCursor.position = 0;
      }

      std::size_t size = BUFFER_BYTES;
      mLastCursor = mRingBuffer.getByCursorOrBack(mLastCursor, buffer, size);

      const bool isMD5Pass = checkMD5(buffer, size);
      const size_t packageNumber = static_cast<size_t>(bufferToInt64(buffer));

      usleep(PROCESSING_TIME_MICROSECONDS);
      const Milliseconds endProcesingTime = getCurrentTime();
      std::cout << "Processed: " << packageNumber << ' ' << endProcesingTime
                << ' ' << (isMD5Pass ? "PASS" : "FAIL") << '\n';
    }
  }

  delete[] buffer;
}

bool BufferReader::checkMD5(unsigned char *data, std::size_t size) {
  unsigned char digest[MD5_BYTES];
  mMD5.prepare();
  mMD5.update(data + DATA_OFFSET, size - DATA_OFFSET - MD5_BYTES);
  mMD5.final(digest);
  return memcmp(digest, data + size - MD5_BYTES, MD5_BYTES) == 0;
}