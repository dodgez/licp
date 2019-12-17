#include "quoted.h"

BOOL isQuote(Stream *stream)
{
  return getStreamChar(stream) == '\'';
}

BOOL isQuoted(Stream *stream)
{
  return isQuote(stream);
}

Node *parseQuoted(Stream *stream)
{
  Node *node = malloc(sizeof(Node));
  node->type = QUOTED_NODE;
  node->value = NULL;
  node->children_size = 0;
  node->children = NULL;
  if (!isQuote(stream))
  {
    throwError("quoted", "'", stream);
    return NULL;
  }
  advanceStream(stream);

  Node *actual = parseAny(stream);
  if (actual == NULL)
  {
    return NULL;
  }
  node->value = actual;

  return node;
}
