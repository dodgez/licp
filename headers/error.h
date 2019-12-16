#ifndef error_h
#define error_h

#include "common.h"
#include "stream.h"

#define MAX_ERROR_MESSAGE_LENGTH 255

char* error_message;

void throwError(char* type, char* expected, Stream* stream);

#endif
