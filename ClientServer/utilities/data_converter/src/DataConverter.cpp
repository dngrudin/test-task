
#include <string.h>

#include "DataConverter.hpp"

namespace {

bool isLittleEndian() {
  const uint16_t x = 0x0001;
  return *((uint8_t *)&x);
}

} // namespace

unsigned char *int64ToBuffer(uint64_t value, unsigned char *dataBuffer) {
  union {
    uint64_t in;
    unsigned char out[8];
  } converter;

  converter.in = value;
  if (isLittleEndian()) {
    dataBuffer[0] = converter.out[7];
    dataBuffer[1] = converter.out[6];
    dataBuffer[2] = converter.out[5];
    dataBuffer[3] = converter.out[4];
    dataBuffer[4] = converter.out[3];
    dataBuffer[5] = converter.out[2];
    dataBuffer[6] = converter.out[1];
    dataBuffer[7] = converter.out[0];
  } else {
    memcpy(dataBuffer, converter.out, sizeof(uint64_t));
  }

  return dataBuffer + sizeof(uint64_t);
}

unsigned char *int16ToBuffer(uint16_t value, unsigned char *dataBuffer) {
  union {
    uint16_t in;
    unsigned char out[2];
  } converter;

  converter.in = value;
  if (isLittleEndian()) {
    dataBuffer[0] = converter.out[1];
    dataBuffer[1] = converter.out[0];
  } else {
    dataBuffer[0] = converter.out[0];
    dataBuffer[1] = converter.out[1];
  }

  return dataBuffer + sizeof(uint16_t);
}

unsigned char *int16ArrayToBuffer(const uint16_t *values, size_t size,
                                  unsigned char *dataBuffer) {
  if (isLittleEndian()) {
    unsigned char *offset = dataBuffer;
    for (size_t i = 0; i < size; ++i) {
      offset = int16ToBuffer(*(values + i), offset);
    }
  } else {
    memcpy(dataBuffer, values, size * sizeof(uint16_t));
  }

  return dataBuffer + size * sizeof(uint16_t);
}

uint64_t bufferToInt64(const unsigned char *dataBuffer) {
  union {
    unsigned char in[8];
    uint64_t out;
  } converter;

  if (isLittleEndian()) {
    converter.in[0] = dataBuffer[7];
    converter.in[1] = dataBuffer[6];
    converter.in[2] = dataBuffer[5];
    converter.in[3] = dataBuffer[4];
    converter.in[4] = dataBuffer[3];
    converter.in[5] = dataBuffer[2];
    converter.in[6] = dataBuffer[1];
    converter.in[7] = dataBuffer[0];
  } else {
    memcpy(converter.in, dataBuffer, sizeof(uint64_t));
  }

  return converter.out;
}