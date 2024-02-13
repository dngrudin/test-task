
#include <stdlib.h>

#include "CommandProcessingFactory.h"
#include "CommandProcessingImpl.h"

struct CommandProcessing *createCommandProcessing() {
  CommandProcessingImpl *commandProcessingImpl =
      (CommandProcessingImpl *)malloc(sizeof(CommandProcessingImpl));

  CommandProcessing *commandProcessing = (CommandProcessing *)malloc(sizeof(CommandProcessing));
  commandProcessing->impl = commandProcessingImpl;
  commandProcessing->procesAmplifierPowerSupplyChange = procesAmplifierPowerSupplyChange;
  commandProcessing->procesTransceiverModeChange = procesTransceiverModeChange;
  return commandProcessing;
}

void deleteCommandProcessing(struct CommandProcessing *commandProcessing) {
  if (commandProcessing != NULL) {
    free(commandProcessing->impl);
    free(commandProcessing);
  }
}
