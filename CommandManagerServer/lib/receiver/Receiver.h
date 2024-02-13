
#ifndef RECEIVER_H
#define RECEIVER_H

#include <stdint.h>

struct Protocol;
struct UdpSocket;

typedef struct Receiver {
  void *impl;

  int (*initReceiver)(struct Receiver *receiver, struct UdpSocket *udpSocket,
                      struct Protocol *protocol);

  int (*runReceiver)(struct Receiver *receiver, uint16_t port);
  int (*stopReceiver)(struct Receiver *receiver);

} Receiver;

#endif // RECEIVER_H