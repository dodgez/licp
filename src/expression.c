#include "expression.h"

BOOL isWhitespace(char c) {
  switch (c) {
    case ' ':
    case '\t':
    case '\r':
    case '\n':
      return TRUE;
    default:
      return FALSE;
  }
}

BOOL isLParen(Stream* stream) {
  return getStreamChar(stream) == '(';
}

BOOL isRParen(Stream* stream) {
  return getStreamChar(stream) == ')';
}

BOOL isExpression(Stream* stream) {
  return isLParen(stream);
}

int parseExpression(Stream* stream, Node* node) {
  node->type = EXPRESSION_NODE;
  node->token = NULL;
  node->children_size = 0;
  int max_length = 10;
  node->children = (Node**)malloc(sizeof(Node*) * max_length);
  memset(node->children, 0, sizeof(Node*) * max_length);

  if (!isLParen(stream)) {
    throwError("expression", "(", stream);
    return 1;
  }
  advanceStream(stream);

  int result;
  while (!isRParen(stream)) {
    result = 1;
    if (isNumber(stream)) {
      node->children[node->children_size] = (Node*)malloc(sizeof(Node*));
      result = parseNumber(stream, node->children[node->children_size]);
    } else if (isId(stream)) {
      node->children[node->children_size] = (Node*)malloc(sizeof(Node*));
      result = parseId(stream, node->children[node->children_size]);
    } else if (isQuotedExpression(stream)) {
      node->children[node->children_size] = (Node*)malloc(sizeof(Node*));
      result = parseQuotedExpression(stream, node->children[node->children_size]);
    } else if (isExpression(stream)) {
      node->children[node->children_size] = (Node*)malloc(sizeof(Node*));
      result = parseExpression(stream, node->children[node->children_size]);
    } else if (isWhitespace(getStreamChar(stream))) {
      advanceStream(stream);
      continue;
    } else {
      throwError("expression", "number", stream);
    }

    if (result != 0) {
      return 1;
    }

    node->children_size += 1;
    if (node->children_size >= max_length) {
      max_length += 10;
      node->children = (Node**)realloc(node->children, sizeof(Node*) * max_length);
      memset(node->children + sizeof(Node*) * node->children_size, 0, sizeof(Node*) * (max_length - node->children_size));
    }
  }

  if (!isRParen(stream)) {
    throwError("expression", ")", stream);
    return 1;
  }
  advanceStream(stream);

  return 0;
}
