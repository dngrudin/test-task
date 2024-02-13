
#ifndef RECEIVER_IMPL_H
#define RECEIVER_IMPL_H

#include <stdatomic.h>
#include <stdint.h>
#include <threads.h>

#include "Receiver.h"

typedef struct ReceiverImpl {
  struct Protocol *protocol;
  struct UdpSocket *socket;
  unsigned char *buffer;

  thrd_t thread;
  atomic_bool isRun;
} ReceiverImpl;

int initReceiver(struct Receiver *receiver, struct UdpSocket *udpSocket, struct Protocol *protocol);

int runReceiver(struct Receiver *receiver, uint16_t port);
int stopReceiver(struct Receiver *receiver);

#endif // RECEIVER_IMPL_H