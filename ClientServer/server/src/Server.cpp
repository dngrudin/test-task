
#include <iostream>
#include <string.h>

#include "Constants.hpp"
#include "DataConverter.hpp"
#include "Time.hpp"

#include "Server.hpp"

#define RING_BUFFER_SIZE 16

Server::Server()
    : mUdpSocket(), mRingBuffer(RING_BUFFER_SIZE, BUFFER_BYTES),
      mBufferReader(mRingBuffer), mMD5(), isRun(false) {}

bool Server::init(uint16_t port) {
  return mUdpSocket.init() && mUdpSocket.bind(port);
}

void Server::run() {
  mBufferReader.start();

  timeval timeout;
  timeout.tv_sec = 0;
  timeout.tv_usec = 500;

  unsigned char *package = new unsigned char[BUFFER_BYTES];

  while (true) {
    if (mUdpSocket.waitData(timeout)) {
      size_t size = mUdpSocket.readData(package, BUFFER_BYTES);
      const Milliseconds receivedTime = getCurrentTime();

      if (size > DATA_OFFSET + MD5_BYTES) {
        mRingBuffer.write(package, size);
        const bool isMD5Pass = checkMD5(package, size);
        const size_t packageNumber =
            static_cast<size_t>(bufferToInt64(package));

        std::cout << "Received: " << packageNumber << ' ' << receivedTime << ' '
                  << (isMD5Pass ? "PASS" : "FAIL") << '\n';
      } else {
        std::cerr << "Received: Data format error\n";
      }
    }
  }
}

bool Server::stop() {
  mBufferReader.stop();
  return true;
}

bool Server::checkMD5(unsigned char *data, std::size_t size) {
  unsigned char digest[MD5_BYTES];
  mMD5.prepare();
  mMD5.update(data + DATA_OFFSET, size - DATA_OFFSET - MD5_BYTES);
  mMD5.final(digest);
  return memcmp(digest, data + size - MD5_BYTES, MD5_BYTES) == 0;
}