
#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stddef.h>

struct CommandHandlers;
struct CommandProcessing;
struct Parser;

enum ComandTag {
  AmplifierPowerSupply = 0x00,
  TransceiverMode = 0x01,
};

typedef struct Protocol {
  void *impl;

  int (*initProtocol)(struct Protocol *protocol, struct CommandHandlers *comandHandlers,
                      struct CommandProcessing *commandProcessing, struct Parser *parser);

  int (*handleData)(struct Protocol *protocol, unsigned char *data, size_t size);

} Protocol;

#endif // PROTOCOL_H