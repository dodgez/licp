#include "number.h"

BOOL isNumber(Stream *stream)
{
  return isdigit((int)getStreamChar(stream));
}

Node *parseNumber(Stream *stream)
{
  BOOL has_decimal = FALSE;
  int i = stream->i;
  while (1)
  {
    char c = getStreamCharIndex(stream, i);
    int is_digit = isdigit((int)c);
    if (is_digit || (!is_digit && c == '.' && has_decimal == FALSE))
    {
      i += 1;
      continue;
    }
    break;
  }

  Node *node = (Node *)malloc(sizeof(Node));
  node->type = NUMBER_NODE;
  node->value = (double *)malloc(sizeof(double));
  char *number = (char *)malloc(sizeof(char) * (i + 1));
  memset(number, 0, sizeof(char) * (i + 1));
  strncpy(number, stream->stream + sizeof(char) * stream->i, i - stream->i);
  ((double *)node->value)[0] = atof(number);
  node->children = NULL;
  node->children_size = 0;
  advanceStreamN(stream, i - stream->i);
  return node;
}
