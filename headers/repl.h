#ifndef repl_h
#define repl_h

#include "common.h"
#include "error.h"
#include "stream.h"
#include "number.h"
#include "id.h"
#include "expression.h"
#include "eval.h"

#define MAX_SPRINTNODE 80

char* sprintNode(Node* node);

void repl(void);

#endif
