
#include <stdlib.h>
#include <string.h>

#include "UdpSocketFactory.h"
#include "UdpSocketImpl.h"

struct UdpSocket *createUdpSocket() {
  UdpSocketImpl *udpSocketImpl = (UdpSocketImpl *)malloc(sizeof(UdpSocketImpl));
  udpSocketImpl->descriptor = -1;
  memset(&udpSocketImpl->address, 0, sizeof(udpSocketImpl->address));

  UdpSocket *udpSocket = (UdpSocket *)malloc(sizeof(UdpSocket));
  udpSocket->impl = udpSocketImpl;
  udpSocket->initSocket = initSocket;
  udpSocket->configureSocket = configureSocket;
  udpSocket->bindSocket = bindSocket;
  udpSocket->stopSocket = stopSocket;
  udpSocket->waitData = waitData;

  return udpSocket;
}

void deleteUdpSocket(struct UdpSocket *udpSocket) {
  if (udpSocket != NULL) {
    udpSocket->stopSocket(udpSocket);
    free(udpSocket->impl);
    free(udpSocket);
  }
}
