
#include <arpa/inet.h>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <netinet/ip.h>
#include <stdlib.h>
#include <unistd.h>

#include "UdpSocket.hpp"

UdpSocket::UdpSocket() : mDescriptor(-1) {}

UdpSocket::~UdpSocket() { stop(); }

bool UdpSocket::init() {
  bool result = false;

  int descriptor = socket(AF_INET, SOCK_DGRAM, 0);
  if (descriptor >= 0) {
    const int flags = fcntl(descriptor, F_GETFL);
    if (fcntl(descriptor, F_SETFL, flags | O_NONBLOCK) >= 0) {
      mDescriptor = descriptor;
      result = true;
    }
  }

  return result;
}

bool UdpSocket::bind(uint16_t port) {
  bool result = false;

  if (mDescriptor >= 0) {
    // setting up destination addres
    memset(&mAddress, 0, sizeof(mAddress));
    mAddress.sin_family = AF_INET;
    mAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    mAddress.sin_port = htons(port);

    // bind to receive address
    if (::bind(mDescriptor, (sockaddr *)(&mAddress), sizeof(mAddress)) == 0) {
      result = true;
    }
  }

  return result;
}

bool UdpSocket::stop() {
  bool result = false;

  if ((mDescriptor >= 0) && (close(mDescriptor) >= 0)) {
    mDescriptor = -1;
    result = true;
  }

  return result;
}

bool UdpSocket::waitData(timeval timeout) {
  bool result = false;

  if (mDescriptor >= 0) {
    fd_set readFDs;
    FD_ZERO(&readFDs);
    FD_SET(mDescriptor, &readFDs);
    const int selectResult =
        select(mDescriptor + 1, &readFDs, NULL, NULL, NULL);

    if (selectResult > 0 && FD_ISSET(mDescriptor, &readFDs)) {
      result = true;
    }
  }

  return result;
}

std::size_t UdpSocket::readData(unsigned char *dataBuffer,
                                std::size_t sizeBuffer) {
  std::size_t result = 0;

  if ((mDescriptor >= 0) && (dataBuffer != NULL)) {
    std::size_t addrlen = sizeof(mAddress);
    result = recvfrom(mDescriptor, dataBuffer, sizeBuffer, 0,
                      (sockaddr *)&mAddress, (socklen_t *)&addrlen);
  }

  return result;
}

std::size_t UdpSocket::sendData(unsigned char *dataBuffer,
                                std::size_t sizeBuffer,
                                const std::string &hostname, uint16_t port) {
  std::size_t result = 0;

  memset(&mAddress, 0, sizeof(mAddress));
  mAddress.sin_family = AF_INET;
  mAddress.sin_addr.s_addr = inet_addr(hostname.c_str());
  mAddress.sin_port = htons(port);

  ssize_t sendBytes = sendto(mDescriptor, dataBuffer, sizeBuffer, MSG_CONFIRM,
                             (const sockaddr *)&mAddress, sizeof(mAddress));
  if (sendBytes > 0) {
    result = sendBytes;
  }

  return result;
}
