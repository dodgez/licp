#ifndef error_h
#define error_h

#include "common.h"
#include "stream.h"

char* error_message;

void throwError(char* type, char* expected, Stream* stream);

#endif
