#ifndef stream_h
#define stream_h

#include "common.h"

typedef struct _Stream {
  char* stream;
  int i;
  int length;
} Stream;

void advanceStream(Stream* stream);
void advanceStreamN(Stream* stream, int n);

char getStreamChar(Stream* stream);
char getStreamCharIndex(Stream* stream, int i);

Stream* getStreamFromString(char* string);

#endif
