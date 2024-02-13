
#ifndef UDP_SOCKET_IMPL_H
#define UDP_SOCKET_IMPL_H

#include <netinet/in.h>
#include <stdint.h>
#include <sys/time.h>

#include "UdpSocket.h"

typedef struct UdpSocketImpl {
  int descriptor;
  struct sockaddr_in address;
} UdpSocketImpl;

int initSocket(struct UdpSocket *udpSocket);
int configureSocket(struct UdpSocket *udpSocket, SocketOptions *options);
int bindSocket(struct UdpSocket *udpSocket, uint16_t port);
int stopSocket(struct UdpSocket *udpSocket);

ssize_t waitData(struct UdpSocket *udpSocket, unsigned char *dataBuffer, size_t sizeBuffer,
                 struct timeval timeout);

#endif // UDP_SOCKET_IMPL_H