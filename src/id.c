#include "id.h"

BOOL isId(Stream* stream) {
  return isalpha((int)getStreamChar(stream));
}

Node* parseId(Stream* stream) {
  int i = stream->i;
  while (isalpha((int)getStreamCharIndex(stream, i))) {
    i += 1;
  }

  Node* node = (Node*)malloc(sizeof(Node));
  node->type = ID_NODE;
  node->value = (char*)malloc(sizeof(char) * (i + 1));
  memset(node->value, 0, sizeof(char) * (i + 1));
  node->children = NULL;
  node->children_size = 0;
  strncpy(node->value, stream->stream + sizeof(char) * stream->i, i-stream->i);
  advanceStreamN(stream, i-stream->i);
  return node;
}
