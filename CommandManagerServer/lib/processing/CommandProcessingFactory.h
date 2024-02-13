
#ifndef COMMAND_PROCESSING_FACTORY_H
#define COMMAND_PROCESSING_FACTORY_H

#include "CommandProcessing.h"

struct CommandProcessing *createCommandProcessing();
void deleteCommandProcessing(struct CommandProcessing *commandProcessing);

#endif // COMMAND_PROCESSING_FACTORY_H