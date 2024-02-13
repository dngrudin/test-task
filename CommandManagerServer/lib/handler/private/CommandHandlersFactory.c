#include <stdlib.h>

#include "CommandHandlersFactory.h"
#include "CommandHandlersImpl.h"

struct CommandHandlers *createCommandHandlers() {
  CommandHandlersImpl *comandHandlersImpl =
      (CommandHandlersImpl *)malloc(sizeof(CommandHandlersImpl));
  comandHandlersImpl->head = NULL;

  CommandHandlers *comandHandlers = (CommandHandlers *)malloc(sizeof(CommandHandlers));
  comandHandlers->impl = comandHandlersImpl;
  comandHandlers->addHandler = addHandler;
  comandHandlers->clearHandlers = clearHandlers;
  comandHandlers->findHandler = findHandler;

  return comandHandlers;
}

void deleteCommandHandlers(struct CommandHandlers *handlers) {
  if (handlers != NULL) {
    handlers->clearHandlers(handlers);
    free(handlers->impl);
    free(handlers);
  }
}
