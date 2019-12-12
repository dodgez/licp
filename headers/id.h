#ifndef id_h
#define id_h

#include "common.h"
#include "stream.h"

BOOL isId(Stream* stream);
int parseId(Stream* stream, Node* node);

#endif
