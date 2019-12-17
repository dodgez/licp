#ifndef parse_any_h
#define parse_any_h

#include "common.h"
#include "error.h"
#include "stream.h"
#include "number.h"
#include "id.h"
#include "expression.h"
#include "quoted.h"

Node *parseAny(Stream *stream);

#endif
