
#include <stdbool.h>
#include <stdlib.h>

#include "Protocol.h"
#include "UdpSocket.h"

#include "ReceiverImpl.h"

#define MAX_DATA_LENGHT (2 + 2 + 0xFFFF)

static int thrRun(void *arg);

int initReceiver(struct Receiver *receiver, struct UdpSocket *udpSocket,
                 struct Protocol *protocol) {
  int result = -1;

  if ((receiver != NULL) && (receiver->impl != NULL) && (udpSocket != NULL) && (protocol != NULL)) {
    ReceiverImpl *implReceiver = (ReceiverImpl *)receiver->impl;

    implReceiver->protocol = protocol;

    implReceiver->socket = udpSocket;

    struct SocketOptions options;
    options.isNoBlocking = 1;
    options.isReusedAddres = 1;
    implReceiver->socket->configureSocket(implReceiver->socket, &options);

    implReceiver->buffer = (unsigned char *)malloc(sizeof(unsigned char) * MAX_DATA_LENGHT);

    result = 0;
  }

  return result;
}

int runReceiver(struct Receiver *receiver, uint16_t port) {
  int resualt = -1;

  if (receiver != NULL) {
    ReceiverImpl *implReceiver = (ReceiverImpl *)receiver->impl;

    bool exp = false;
    if (atomic_compare_exchange_strong(&implReceiver->isRun, &exp, true)) {
      resualt = implReceiver->socket->bindSocket(implReceiver->socket, port);

      if ((resualt >= 0) &&
          (thrd_create(&implReceiver->thread, thrRun, (void *)implReceiver) == thrd_success)) {
        resualt = 0;
      }
    }
  }

  return resualt;
}

int stopReceiver(struct Receiver *receiver) {
  int resualt = -1;

  if (receiver != NULL) {
    ReceiverImpl *implReceiver = (ReceiverImpl *)receiver->impl;

    bool exp = true;
    if (atomic_compare_exchange_strong(&implReceiver->isRun, &exp, false)) {
      implReceiver->isRun = false;
      thrd_join(implReceiver->thread, NULL);

      resualt = 0;
    }
  }

  return resualt;
}

static int thrRun(void *arg) {
  ReceiverImpl *implReceiver = (ReceiverImpl *)arg;

  struct timeval timeout;
  timeout.tv_sec = 0;
  timeout.tv_usec = 500;

  while (atomic_load_explicit(&implReceiver->isRun, memory_order_relaxed)) {
    ssize_t readBytes = implReceiver->socket->waitData(implReceiver->socket, implReceiver->buffer,
                                                       MAX_DATA_LENGHT, timeout);
    if (readBytes > 0) {
      implReceiver->protocol->handleData(implReceiver->protocol, implReceiver->buffer, readBytes);
    }
  }

  return 0;
}