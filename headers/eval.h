#ifndef eval_h
#define eval_h

#include "common.h"

#define NUMBER_VALUE 0

typedef struct _Value {
  int type;
  void* data;
} Value;

int eval(Node* node, Value* result);

#endif