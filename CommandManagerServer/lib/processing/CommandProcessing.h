
#ifndef COMMAND_PROCESSING_H
#define COMMAND_PROCESSING_H

#include <stdint.h>

typedef struct CommandProcessing {
  void *impl;

  void (*procesTransceiverModeChange)(struct CommandProcessing *commandProcessing, char *mode);
  void (*procesAmplifierPowerSupplyChange)(struct CommandProcessing *commandProcessing, int8_t on);

} CommandProcessing;

#endif // COMMAND_PROCESSING_H