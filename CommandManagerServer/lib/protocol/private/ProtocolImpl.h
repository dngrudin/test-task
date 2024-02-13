
#ifndef PROTOCOL_IMPL_H
#define PROTOCOL_IMPL_H

#include "Protocol.h"

typedef struct ProtocolImpl {
  struct CommandHandlers *commandHandlers;
  struct CommandProcessing *commandProcessing;
  struct Parser *parser;
} ProtocolImpl;

int initProtocol(struct Protocol *protocol, struct CommandHandlers *commandHandlers,
                 struct CommandProcessing *commandProcessing, struct Parser *parser);

int handleData(struct Protocol *protocol, unsigned char *data, size_t size);

#endif // PROTOCOL_IMPL_H