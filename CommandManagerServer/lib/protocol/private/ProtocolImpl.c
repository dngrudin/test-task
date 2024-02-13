
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "CommandHandlers.h"
#include "CommandProcessing.h"
#include "Parser.h"

#include "ProtocolImpl.h"

static void logData(unsigned char *data, size_t size);

static void parseTransceiverModeData(unsigned char *data, size_t dataSize, void *self);
static void parseAmplifierPowerSupplyData(unsigned char *data, size_t dataSize, void *self);

int initProtocol(struct Protocol *protocol, struct CommandHandlers *comandHandlers,
                 struct CommandProcessing *commandProcessing, struct Parser *parser) {
  int result = -1;

  if ((protocol != NULL) && (protocol->impl != NULL) && (comandHandlers != NULL) &&
      (commandProcessing != NULL) && (parser != NULL)) {
    ProtocolImpl *implProtocol = (ProtocolImpl *)protocol->impl;

    implProtocol->commandHandlers = comandHandlers;
    implProtocol->commandHandlers->addHandler(implProtocol->commandHandlers, AmplifierPowerSupply,
                                              parseAmplifierPowerSupplyData);
    implProtocol->commandHandlers->addHandler(implProtocol->commandHandlers, TransceiverMode,
                                              parseTransceiverModeData);

    implProtocol->commandProcessing = commandProcessing;

    implProtocol->parser = parser;
    implProtocol->parser->configure(implProtocol->parser, BigEndian);

    result = 0;
  }

  return result;
}

int handleData(struct Protocol *protocol, unsigned char *data, size_t size) {
  int result = -1;

  if ((protocol != NULL) && (protocol->impl != NULL)) {
    ProtocolImpl *implProtocol = (ProtocolImpl *)protocol->impl;

    if ((size > 0) && (data != NULL)) {
      unsigned char *current = data;
      ssize_t byteToEnd = size;

      while (byteToEnd >= 0) {
        unsigned char *begin = current;

        uint16_t comandTag = 0;
        size_t countTagByte =
            implProtocol->parser->getUInt16(implProtocol->parser, current, byteToEnd, &comandTag);
        current += countTagByte;
        byteToEnd -= countTagByte;

        uint16_t comandLenght = 0;
        size_t countLenghtByte = implProtocol->parser->getUInt16(implProtocol->parser, current,
                                                                 byteToEnd, &comandLenght);
        current += countLenghtByte;
        byteToEnd -= countLenghtByte;

        if ((countTagByte > 0) && (countLenghtByte > 0) && (byteToEnd >= comandLenght)) {
          Handler handler =
              implProtocol->commandHandlers->findHandler(implProtocol->commandHandlers, comandTag);
          if (handler != NULL) {
            logData(begin, countTagByte + countLenghtByte + comandLenght);
            handler(current, comandLenght, implProtocol);
          }

          current += comandLenght;
          byteToEnd -= comandLenght;
        } else {
          break;
        }
      };
    }

    result = 0;
  }

  return result;
}

static void logData(unsigned char *data, size_t size) {
  printf("Data: ");
  for (size_t i = 0; i < size; ++i) {
    printf("0x%02X ", *(data + i));
  }
  printf("\n");
}

static void parseTransceiverModeData(unsigned char *data, size_t dataSize, void *self) {
  ProtocolImpl *implProtocol = (ProtocolImpl *)self;
  char *mode = (char *)malloc(dataSize);
  if (implProtocol->parser->getString(implProtocol->parser, data, dataSize, &mode) > 0) {
    implProtocol->commandProcessing->procesTransceiverModeChange(implProtocol->commandProcessing,
                                                                 mode);
  }
}

static void parseAmplifierPowerSupplyData(unsigned char *data, size_t dataSize, void *self) {
  ProtocolImpl *implProtocol = (ProtocolImpl *)self;
  int8_t on = 0;
  if (implProtocol->parser->getInt8(implProtocol->parser, data, dataSize, &on) > 0) {
    implProtocol->commandProcessing->procesAmplifierPowerSupplyChange(
        implProtocol->commandProcessing, on);
  }
}