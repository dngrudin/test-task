
#ifndef PROTOCOL_FACTORY_H
#define PROTOCOL_FACTORY_H

#include "Protocol.h"

struct Protocol *createProtocol();
void deleteProtocol(struct Protocol *protocol);

#endif // PROTOCOL_FACTORY_H