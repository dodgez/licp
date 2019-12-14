#ifndef eval_h
#define eval_h

#include "common.h"

#define NUMBER_VALUE 0

typedef struct _Value {
  int type;
  void* data;
} Value;

typedef struct _Var {
  char* name;
  Value* data;
} Var;

Var* variables;
int variable_count;
int allocated_variables;

void addVariable(Var* variable);
Var* getVariable(char* name);
Value* eval(Node* node);

#endif