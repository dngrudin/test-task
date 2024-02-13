
#ifndef PARSER_H
#define PARSER_H

#include <stddef.h>
#include <stdint.h>

enum ByteSequence { LittleEndian, BigEndian };

typedef struct Parser {
  void *impl;

  void (*configure)(struct Parser *parcer, enum ByteSequence inputByteSequence);

  size_t (*getInt8)(struct Parser *parcer, unsigned char *data, size_t size, int8_t *result);
  size_t (*getUInt8)(struct Parser *parcer, unsigned char *data, size_t size, uint8_t *result);

  size_t (*getInt16)(struct Parser *parcer, unsigned char *data, size_t size, int16_t *result);
  size_t (*getUInt16)(struct Parser *parcer, unsigned char *data, size_t size, uint16_t *result);

  size_t (*getString)(struct Parser *parcer, unsigned char *data, size_t size, char **result);

} Parser;

#endif // PARSER_H