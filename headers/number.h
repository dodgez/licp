#ifndef number_h
#define number_h

#include "common.h"
#include "stream.h"

BOOL isNumber(Stream* stream);
int parseNumber(Stream* stream, Node* node);

#endif
