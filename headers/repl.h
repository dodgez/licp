#ifndef repl_h
#define repl_h

#include "common.h"
#include "error.h"
#include "stream.h"
#include "parse_any.h"
#include "eval.h"

#define MAX_SPRINTNODE_LENGTH 80

char *sprintNode(Node *node);

void repl(void);

#endif
