#include "quoted_expression.h"

BOOL isQuote(Stream *stream)
{
  return getStreamChar(stream) == '\'';
}

BOOL isQuotedExpression(Stream *stream)
{
  return isQuote(stream);
}

Node *parseQuotedExpression(Stream *stream)
{
  if (!isQuote(stream))
  {
    throwError("quoted_expression", "'", stream);
    return NULL;
  }
  advanceStream(stream);

  if (!isExpression(stream))
  {
    throwError("quoted_expression", "expression", stream);
    return NULL;
  }

  Node *node = parseExpression(stream);
  if (node == NULL)
  {
    return NULL;
  }
  node->type = QUOTED_EXPRESSION_NODE;

  return node;
}
