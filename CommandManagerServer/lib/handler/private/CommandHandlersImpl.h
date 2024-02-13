
#ifndef COMMAND_HANDLERS_IMPL_H
#define COMMAND_HANDLERS_IMPL_H

#include "CommandHandlers.h"

typedef struct ComandHandler {
  DataTag tag;
  Handler handler;

  struct ComandHandler *next;
} ComandHandler;

typedef struct CommandHandlersImpl {
  struct ComandHandler *head;
} CommandHandlersImpl;

void addHandler(struct CommandHandlers *cmdHandlers, DataTag tag, Handler handler);

void clearHandlers(struct CommandHandlers *cmdHandlers);

Handler findHandler(struct CommandHandlers *cmdHandlers, DataTag tag);

#endif // COMMAND_HANDLERS_IMPL_H