
#ifndef COMMAND_HANDLERS_H
#define COMMAND_HANDLERS_H

#include <stddef.h>
#include <stdint.h>

typedef uint16_t DataTag;
typedef unsigned char *Data;

typedef void (*Handler)(Data, size_t, void *);

typedef struct CommandHandlers {
  void *impl;

  void (*addHandler)(struct CommandHandlers *handlers, DataTag tag, Handler handler);
  void (*clearHandlers)(struct CommandHandlers *handlers);
  Handler (*findHandler)(struct CommandHandlers *handlers, DataTag tag);

} CommandHandlers;

#endif // COMMAND_HANDLERS_H