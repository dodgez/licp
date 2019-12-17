#ifndef quoted_h
#define quoted_h

#include "common.h"
#include "error.h"
#include "stream.h"
#include "parse_any.h"

BOOL isQuote(Stream *stream);

BOOL isQuoted(Stream *stream);
Node *parseQuoted(Stream *stream);

#endif
