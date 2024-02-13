
#ifndef PARSER_FACTORY_H
#define PARSER_FACTORY_H

#include "Parser.h"

struct Parser *createParser();
void deleteParser(struct Parser *parser);

#endif // PARSER_FACTORY_H