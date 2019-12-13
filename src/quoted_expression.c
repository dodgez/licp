#include "quoted_expression.h"

BOOL isQuote(Stream* stream) {
  return getStreamChar(stream) == '\'';
}

BOOL isQuotedExpression(Stream* stream) {
  return isQuote(stream);
}

int parseQuotedExpression(Stream* stream, Node* node) {
  if (!isQuote(stream)) {
    throwError("quoted_expression", "'", stream);
    return 1;
  }
  advanceStream(stream);

  if (!isExpression(stream)) {
    throwError("quoted_expression", "expression", stream);
    return 1;
  }

  if (parseExpression(stream, node) != 0) {
    return 1;
  }
  node->type = QUOTED_EXPRESSION_NODE;

  return 0;
}
