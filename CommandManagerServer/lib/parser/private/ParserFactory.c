
#include <stdlib.h>

#include "ParserFactory.h"
#include "ParserImpl.h"

static enum ByteSequence getByteSequence();

struct Parser *createParser() {
  ParserImpl *parserImpl = (ParserImpl *)malloc(sizeof(ParserImpl));
  parserImpl->outputByteSequence = getByteSequence();
  parserImpl->inputByteSequence = BigEndian;

  Parser *parser = (Parser *)malloc(sizeof(Parser));
  parser->impl = parserImpl;
  parser->configure = configure;
  parser->getInt8 = getInt8;
  parser->getUInt8 = getUInt8;
  parser->getInt16 = getInt16;
  parser->getUInt16 = getUInt16;
  parser->getString = getString;

  return parser;
}

void deleteParser(struct Parser *parser) {
  if (parser != NULL) {
    free(parser->impl);
    free(parser);
  }
}

static enum ByteSequence getByteSequence() {
  const uint16_t x = 0x0001;
  return *((uint8_t *)&x) ? LittleEndian : BigEndian;
}