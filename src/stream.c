#include "stream.h"

void advanceStream(Stream *stream)
{
  stream->i += sizeof(char);
}

void advanceStreamN(Stream *stream, int n)
{
  stream->i += sizeof(char) * n;
}

char getStreamChar(Stream *stream)
{
  if (stream->i >= stream->length)
  {
    return -1;
  }
  else
  {
    return stream->stream[stream->i];
  }
}

char getStreamCharIndex(Stream *stream, int i)
{
  if (i >= stream->length)
  {
    return -1;
  }
  else
  {
    return stream->stream[i];
  }
}

Stream *getStreamFromString(char *string)
{
  Stream *stream = (Stream *)malloc(sizeof(Stream));
  stream->stream = string;
  stream->i = 0;
  stream->length = strlen(string);

  return stream;
}
