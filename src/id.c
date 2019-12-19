#include "id.h"

BOOL isId(Stream *stream)
{
  return isalpha((int)getStreamChar(stream));
}

Node *parseId(Stream *stream)
{
  int i = stream->i;
  while (isalpha((int)getStreamCharIndex(stream, i)))
  {
    i += 1;
  }

  Node *node = (Node *)malloc(sizeof(Node));
  if (i >= 4 && strncmp(stream->stream + sizeof(char) * i, "true", 4) == 0)
  {
    i = 4;
    node->type = BOOLEAN_NODE;
    node->value = (int *)malloc(sizeof(int));
    ((int *)node->value)[0] = 1;
  }
  else if (i >= 5 && strncmp(stream->stream + sizeof(char) * i, "false", 5) == 0)
  {
    i = 5;
    node->type = BOOLEAN_NODE;
    node->value = (int *)malloc(sizeof(int));
    ((int *)node->value)[0] = 0;
  }
  else
  {
    node->type = ID_NODE;
    node->value = (char *)malloc(sizeof(char) * (i + 1));
    memset(node->value, 0, sizeof(char) * (i + 1));
    strncpy(node->value, stream->stream + sizeof(char) * stream->i, i - stream->i);
  }

  node->children = NULL;
  node->children_size = 0;
  advanceStreamN(stream, i - stream->i);
  return node;
}
