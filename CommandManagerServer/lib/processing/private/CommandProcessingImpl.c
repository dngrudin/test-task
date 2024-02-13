
#include <stdio.h>
#include <stdlib.h>

#include "CommandProcessing.h"
#include "CommandProcessingImpl.h"

void procesTransceiverModeChange(struct CommandProcessing *commandProcessing, char *mode) {
  if (commandProcessing != NULL) {
    fprintf(stderr, "TransceiverMode: %s\n", mode);
    free(mode);
  }
}

void procesAmplifierPowerSupplyChange(struct CommandProcessing *commandProcessing, int8_t on) {
  if (commandProcessing != NULL) {
    fprintf(stderr, "AmplifierPowerSupply: %s\n", on ? "on" : "off");
  }
}