
#ifndef SERVER_HPP
#define SERVER_HPP

#include <stdint.h>

#include "BufferReader.hpp"
#include "MD5.hpp"
#include "RingBuffer.hpp"
#include "UdpSocket.hpp"

class Server {
public:
  Server();

  bool init(uint16_t port);

  void run();

  bool stop();

private:
  bool checkMD5(unsigned char *data, std::size_t size);

  UdpSocket mUdpSocket;
  RingBuffer mRingBuffer;
  BufferReader mBufferReader;
  MD5 mMD5;
  bool isRun;
};

#endif // SERVER_HPP