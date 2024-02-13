
#include <stdbool.h>
#include <stdlib.h>

#include "ReceiverFactory.h"
#include "ReceiverImpl.h"

struct Receiver *createReceiver() {
  ReceiverImpl *receiverImpl = (ReceiverImpl *)malloc(sizeof(ReceiverImpl));
  receiverImpl->protocol = NULL;
  receiverImpl->socket = NULL;
  receiverImpl->buffer = NULL;
  receiverImpl->thread = 0;
  atomic_init(&receiverImpl->isRun, false);

  Receiver *receiver = (Receiver *)malloc(sizeof(Receiver));
  receiver->impl = receiverImpl;
  receiver->initReceiver = initReceiver;
  receiver->runReceiver = runReceiver;
  receiver->stopReceiver = stopReceiver;

  return receiver;
}

void deleteReceiver(struct Receiver *receiver) {
  if (receiver != NULL) {
    receiver->stopReceiver(receiver);
    free(receiver->impl);
    free(receiver);
  }
}
