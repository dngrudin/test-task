
#ifndef COMMAND_HANDLER_FACTORY_H
#define COMMAND_HANDLER_FACTORY_H

#include "CommandHandlers.h"

struct CommandHandlers *createCommandHandlers();
void deleteCommandHandlers(struct CommandHandlers *commandHandlers);

#endif // COMMAND_HANDLER_FACTORY_H