#ifndef expression_h
#define expression_h

#include "common.h"
#include "error.h"
#include "stream.h"
#include "number.h"
#include "id.h"
#include "quoted.h"

BOOL isWhitespace(char c);

BOOL isLParen(Stream *stream);
BOOL isRParen(Stream *stream);

BOOL isExpression(Stream *stream);
Node *parseExpression(Stream *stream);

#endif
