#include "expression.h"

BOOL isWhitespace(char c)
{
  switch (c)
  {
  case ' ':
  case '\t':
  case '\r':
  case '\n':
    return TRUE;
  default:
    return FALSE;
  }
}

BOOL isLParen(Stream *stream)
{
  return getStreamChar(stream) == '(';
}

BOOL isRParen(Stream *stream)
{
  return getStreamChar(stream) == ')';
}

BOOL isExpression(Stream *stream)
{
  return isLParen(stream);
}

Node *parseExpression(Stream *stream)
{
  Node *node = (Node *)malloc(sizeof(Node));
  node->type = EXPRESSION_NODE;
  node->value = NULL;
  node->children_size = 0;
  int max_length = 10;
  node->children = (Node **)malloc(sizeof(Node *) * max_length);
  memset(node->children, 0, sizeof(Node *) * max_length);

  if (!isLParen(stream))
  {
    throwError("expression", "(", stream);
    return NULL;
  }
  advanceStream(stream);

  while (!isRParen(stream))
  {
    if (isNumber(stream))
    {
      node->children[node->children_size] = parseNumber(stream);
    }
    else if (isId(stream))
    {
      node->children[node->children_size] = parseId(stream);
    }
    else if (isExpression(stream))
    {
      node->children[node->children_size] = parseExpression(stream);
    }
    else if (isQuoted(stream))
    {
      node->children[node->children_size] = parseQuoted(stream);
    }
    else if (isWhitespace(getStreamChar(stream)))
    {
      advanceStream(stream);
      continue;
    }
    else
    {
      throwError("expression", "number or id or expression or quoted or whitespace", stream);
      return NULL;
    }

    if (node->children[node->children_size] == NULL)
    {
      return NULL;
    }

    node->children_size += 1;
    if (node->children_size >= max_length)
    {
      max_length += 10;
      node->children = (Node **)realloc(node->children, sizeof(Node *) * max_length);
      memset(node->children + sizeof(Node *) * node->children_size, 0, sizeof(Node *) * (max_length - node->children_size));
    }
  }

  if (!isRParen(stream))
  {
    throwError("expression", ")", stream);
    return NULL;
  }
  advanceStream(stream);

  return node;
}
