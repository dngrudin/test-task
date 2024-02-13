
#include <stdlib.h>

#include "CommandHandlers.h"
#include "CommandHandlersImpl.h"

void addHandler(struct CommandHandlers *cmdHandlers, DataTag tag, Handler handler) {
  if (cmdHandlers != NULL) {
    CommandHandlersImpl *implHandlers = (CommandHandlersImpl *)cmdHandlers->impl;

    struct ComandHandler *newComandHandler =
        (struct ComandHandler *)malloc(sizeof(struct ComandHandler));
    newComandHandler->tag = tag;
    newComandHandler->handler = handler;
    newComandHandler->next = NULL;

    if (implHandlers->head == NULL) {
      implHandlers->head = newComandHandler;
    } else {
      struct ComandHandler *comandHandler = implHandlers->head;
      while (comandHandler->next != NULL) {
        comandHandler = comandHandler->next;
      }
      comandHandler->next = newComandHandler;
    }
  }
}

void clearHandlers(struct CommandHandlers *cmdHandlers) {
  if (cmdHandlers != NULL) {
    CommandHandlersImpl *implHandlers = (CommandHandlersImpl *)cmdHandlers->impl;

    if (implHandlers->head != NULL) {
      ComandHandler *comandHandler = implHandlers->head;
      while (comandHandler != NULL) {
        ComandHandler *toFreeComandHandler = comandHandler;
        comandHandler = comandHandler->next;
        free(toFreeComandHandler);
      }

      implHandlers->head = NULL;
    }
  }
}

Handler findHandler(struct CommandHandlers *cmdHandlers, DataTag tag) {
  Handler handler = NULL;

  if (cmdHandlers != NULL) {
    CommandHandlersImpl *implHandlers = (CommandHandlersImpl *)cmdHandlers->impl;

    ComandHandler *comandHandler = implHandlers->head;

    while (comandHandler != NULL) {
      if (comandHandler->tag == tag) {
        handler = comandHandler->handler;
        break;
      }
      comandHandler = comandHandler->next;
    }
  }

  return handler;
}