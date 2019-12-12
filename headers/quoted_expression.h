#ifndef quoted_expression_h
#define quoted_expression_h

#include "common.h"
#include "error.h"
#include "stream.h"
#include "expression.h"

BOOL isQuote(Stream* stream);

BOOL isQuotedExpression(Stream* stream);
int parseQuotedExpression(Stream* stream, Node* node);

#endif
