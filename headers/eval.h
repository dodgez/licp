#ifndef eval_h
#define eval_h

#include "common.h"

typedef struct Variable
{
  char *name;
  Node *value;
} Variable;

int expectNumberNode(Node *node);
int expectIdNode(Node *node);
int expectExpressionNode(Node *node);

int expectNArguments(Node *node, int n);
int expectExactlyNArguments(Node *node, int n);

Node *getVariable(char *id);
void setVariable(char *id, Node *value);

Node *eval(Node *node);
Node *evalExpression(Node *node);
Node *evalFunction(Node *node, Node *function);

Variable *variables;
int variable_count;
int max_variables;

#endif
