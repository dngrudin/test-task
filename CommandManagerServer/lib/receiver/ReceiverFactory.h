
#ifndef RECIEVER_FACTORY_H
#define RECIEVER_FACTORY_H

#include "Receiver.h"

struct Receiver *createReceiver();
void deleteReceiver(struct Receiver *receiver);

#endif // RECIEVER_FACTORY_H