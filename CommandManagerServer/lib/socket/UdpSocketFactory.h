
#ifndef UDP_SOCKET_FACTORY_H
#define UDP_SOCKET_FACTORY_H

#include "UdpSocket.h"

struct UdpSocket *createUdpSocket();
void deleteUdpSocket(struct UdpSocket *udpSocket);

#endif // UDP_SOCKET_FACTORY_H