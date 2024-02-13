
#include <stdlib.h>
#include <string.h>

#include "ParserImpl.h"

void configure(struct Parser *parser, enum ByteSequence inputByteSequence) {
  if (parser != NULL) {
    ParserImpl *implParser = (ParserImpl *)parser->impl;

    implParser->inputByteSequence = inputByteSequence;
  }
}

size_t getUInt8(struct Parser *parser, unsigned char *data, size_t size, uint8_t *parcerResult) {
  size_t result = 0;

  if ((parser != NULL) && (data != NULL)) {
    ParserImpl *implParser = (ParserImpl *)parser->impl;
    (void)implParser;

    const size_t minSize = sizeof(uint8_t);
    if (size >= minSize) {
      if (parcerResult != NULL) {
        *parcerResult = *data;
      }

      result = minSize;
    }
  }
  return result;
}

size_t getInt8(struct Parser *parser, unsigned char *data, size_t size, int8_t *parcerResult) {
  return getUInt8(parser, data, size, (uint8_t *)parcerResult);
}

size_t getUInt16(struct Parser *parser, unsigned char *data, size_t size, uint16_t *parcerResult) {
  size_t result = 0;

  if ((parser != NULL) && (data != NULL)) {
    ParserImpl *implParser = (ParserImpl *)parser->impl;

    union ToUInt16 {
      unsigned char in[2];
      uint16_t out;
    } toUInt16;

    const size_t minSize = sizeof(toUInt16);
    if (size >= minSize) {
      if (parcerResult != NULL) {
        if (implParser->inputByteSequence == implParser->outputByteSequence) {
          toUInt16.in[0] = *data;
          toUInt16.in[1] = *(data + 1);
        } else {
          toUInt16.in[0] = *(data + 1);
          toUInt16.in[1] = *data;
        }
        *parcerResult = toUInt16.out;
      }

      result = minSize;
    }
  }

  return result;
}

size_t getInt16(struct Parser *parser, unsigned char *data, size_t size, int16_t *parcerResult) {
  return getUInt16(parser, data, size, (uint16_t *)parcerResult);
}

size_t getString(struct Parser *parser, unsigned char *data, size_t size, char **parcerResult) {
  size_t result = 0;

  if ((parser != NULL) && (data != NULL)) {
    ParserImpl *implParser = (ParserImpl *)parser->impl;
    (void)implParser;

    if (*parcerResult != NULL) {
      memcpy(*parcerResult, data, size);
    }

    result = size;
  }

  return result;
}
