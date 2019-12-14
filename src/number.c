#include "number.h"

BOOL isNumber(Stream* stream) {
  return isdigit((int)getStreamChar(stream));
}

Node* parseNumber(Stream* stream) {
  BOOL is_digit = TRUE;
  int i = stream->i;
  while (isdigit((int)getStreamCharIndex(stream, i))) {
    i += 1;
  }

  Node* node = (Node*)malloc(sizeof(Node));
  node->type = NUMBER_NODE;
  node->token = (char*)malloc(sizeof(char) * i);
  node->children = NULL;
  node->children_size = 0;
  strncpy(node->token, stream->stream + sizeof(char) * stream->i, i-stream->i);
  advanceStreamN(stream, i-stream->i);
  return node;
}
