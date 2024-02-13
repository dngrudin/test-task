
#ifndef UDP_SOCKET_H
#define UDP_SOCKET_H

#include <stddef.h>
#include <stdint.h>
#include <sys/time.h>
#include <sys/types.h>

typedef struct SocketOptions {
  int isNoBlocking;
  int isReusedAddres;
} SocketOptions;

typedef struct UdpSocket {
  void *impl;

  int (*initSocket)(struct UdpSocket *udpSocket);
  int (*configureSocket)(struct UdpSocket *udpSocket, SocketOptions *options);
  int (*bindSocket)(struct UdpSocket *udpSocket, uint16_t port);
  int (*stopSocket)(struct UdpSocket *udpSocket);

  ssize_t (*waitData)(struct UdpSocket *udpSocket, unsigned char *dataBuffer, size_t sizeBuffer,
                      struct timeval timeout);

} UdpSocket;

#endif // UDP_SOCKET_H