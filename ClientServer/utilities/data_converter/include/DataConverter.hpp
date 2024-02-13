#ifndef DATA_CONVERTER_HPP
#define DATA_CONVERTER_HPP

#include <cstddef>
#include <stdint.h>

unsigned char *int64ToBuffer(uint64_t value, unsigned char *dataBuffer);
unsigned char *int16ToBuffer(uint16_t value, unsigned char *dataBuffer);
unsigned char *int16ArrayToBuffer(const uint16_t *values, size_t size,
                                  unsigned char *dataBuffer);

uint64_t bufferToInt64(const unsigned char *dataBuffer);

#endif // DATA_CONVERTER_HPP