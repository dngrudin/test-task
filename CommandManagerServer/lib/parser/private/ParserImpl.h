
#ifndef PARSER_IMPL_H
#define PARSER_IMPL_H

#include "Parser.h"

typedef struct ParserImpl {
  enum ByteSequence outputByteSequence;
  enum ByteSequence inputByteSequence;
} ParserImpl;

void configure(struct Parser *parser, enum ByteSequence inputByteSequence);

size_t getInt8(struct Parser *parser, unsigned char *data, size_t size, int8_t *result);
size_t getUInt8(struct Parser *parser, unsigned char *data, size_t size, uint8_t *result);

size_t getInt16(struct Parser *parser, unsigned char *data, size_t size, int16_t *result);
size_t getUInt16(struct Parser *parser, unsigned char *data, size_t size, uint16_t *result);

size_t getString(struct Parser *parser, unsigned char *data, size_t size, char **result);

#endif // PARSER_IMPL_H