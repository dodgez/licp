#ifndef eval_h
#define eval_h

#include "common.h"

typedef struct Variable
{
  char *name;
  Node *value;
  struct Variable *next;
  struct Variable *backup;
} Variable;

int expectNumberNode(Node *node);
int expectIdNode(Node *node);
int expectExpressionNode(Node *node);

int expectNArguments(Node *node, int n);
int expectExactlyNArguments(Node *node, int n);

Node *getVariable(char *id);
void setVariable(char *id, Node *value, BOOL backup);
void removeVariable(char *id);

Node *eval(Node *node);
Node *evalExpression(Node *node);
Node *evalFunction(Node *node, Node *function);

Variable *variables;

#endif
