
#include <errno.h>
#include <fcntl.h>
#include <netinet/ip.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "UdpSocketImpl.h"

int initSocket(struct UdpSocket *udpSocket) {
  int result = -1;

  if (udpSocket != NULL) {
    UdpSocketImpl *implUdpSocket = (UdpSocketImpl *)udpSocket->impl;

    int descriptor = socket(AF_INET, SOCK_DGRAM, 0);
    if (descriptor >= 0) {
      implUdpSocket->descriptor = descriptor;
      result = 0;
    }
  }

  return result;
}

int configureSocket(struct UdpSocket *udpSocket, SocketOptions *options) {
  int result = -1;

  if (udpSocket != NULL) {
    UdpSocketImpl *implUdpSocket = (UdpSocketImpl *)udpSocket->impl;

    if (options != NULL) {
      // allow multiple sockets to use the same PORT number
      const int isReusedAddres = options->isReusedAddres;
      result = setsockopt(implUdpSocket->descriptor, SOL_SOCKET, SO_REUSEADDR, &isReusedAddres,
                          sizeof(isReusedAddres));

      int flags = fcntl(implUdpSocket->descriptor, F_GETFL);
      result = fcntl(implUdpSocket->descriptor, F_SETFL,
                     options->isNoBlocking ? (flags | O_NONBLOCK) : (flags & ~O_NONBLOCK));
    }
  }

  return result;
}

int bindSocket(struct UdpSocket *udpSocket, uint16_t port) {
  int result = -1;

  if (udpSocket != NULL) {
    UdpSocketImpl *implUdpSocket = (UdpSocketImpl *)udpSocket->impl;

    // setting up destination addres
    memset(&implUdpSocket->address, 0, sizeof(implUdpSocket->address));
    implUdpSocket->address.sin_family = AF_INET;
    implUdpSocket->address.sin_addr.s_addr = htonl(INADDR_ANY);
    implUdpSocket->address.sin_port = htons(port);

    // bind to receive address
    result = bind(implUdpSocket->descriptor, (struct sockaddr *)&implUdpSocket->address,
                  sizeof(implUdpSocket->address));
  }

  return result;
}

int stopSocket(struct UdpSocket *udpSocket) {
  int result = -1;

  if (udpSocket != NULL) {
    UdpSocketImpl *implUdpSocket = (UdpSocketImpl *)udpSocket->impl;

    result = shutdown(implUdpSocket->descriptor, SHUT_RDWR);
    if (result >= 0) {
      result = close(implUdpSocket->descriptor);
    }
  }
  return result;
}

ssize_t waitData(struct UdpSocket *udpSocket, unsigned char *dataBuffer, size_t sizeBuffer,
                 struct timeval timeout) {
  ssize_t result = -1;

  if (udpSocket != NULL) {
    UdpSocketImpl *implUdpSocket = (UdpSocketImpl *)udpSocket->impl;

    fd_set readFDs;
    FD_ZERO(&readFDs);
    FD_SET(implUdpSocket->descriptor, &readFDs);
    result = select(implUdpSocket->descriptor + 1, &readFDs, NULL, NULL, &timeout);

    if (result > 0 && FD_ISSET(implUdpSocket->descriptor, &readFDs)) {
      size_t addrlen = sizeof(implUdpSocket->address);
      result = recvfrom(implUdpSocket->descriptor, dataBuffer, sizeBuffer, MSG_WAITALL,
                        (struct sockaddr *)&implUdpSocket->address, (socklen_t *)&addrlen);
    }
  }

  return result;
}
