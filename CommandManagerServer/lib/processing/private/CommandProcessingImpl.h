
#ifndef COMMAND_PROCESSING_IMPL_H
#define COMMAND_PROCESSING_IMPL_H

#include <stdint.h>

struct CommandProcessing;

typedef struct CommandProcessingImpl {

} CommandProcessingImpl;

void procesTransceiverModeChange(struct CommandProcessing *commandProcessing, char *mode);
void procesAmplifierPowerSupplyChange(struct CommandProcessing *commandProcessing, int8_t on);

#endif // COMMAND_PROCESSING_IMPL_H