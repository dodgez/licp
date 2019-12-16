#include "eval.h"

int expectNumberNode(Node *node)
{
  if (node->type != NUMBER_NODE)
  {
    printf("Error: expected type 'number' but got type '%d'\n", node->type);
    return 1;
  }
  return 0;
}
int expectIdNode(Node *node)
{
  if (node->type != ID_NODE)
  {
    printf("Error: expected type 'id' but got type '%d'\n", node->type);
    return 1;
  }
  return 0;
}
int expectExpressionNode(Node *node)
{
  if (node->type != EXPRESSION_NODE)
  {
    printf("Error: expected type 'expression' but got type '%d'\n", node->type);
    return 1;
  }
  return 0;
}

int expectNArguments(Node *node, int n)
{
  if (node->children_size < n)
  {
    printf("Error: expected function to have at least %d arguments but got %d\n", n, node->children_size);
    return 1;
  }
  return 0;
}
int expectExactlyNArguments(Node *node, int n)
{
  if (node->children_size != n)
  {
    printf("Error: expected function to have exactly %d arguments but got %d\n", n, node->children_size);
    return 1;
  }
  return 0;
}

Node *getVariable(char *id)
{
  for (int i = 0; i < variable_count; ++i)
  {
    if (strcmp(variables[i].name, id) == 0)
    {
      return variables[i].value;
    }
  }
  return NULL;
}
void setVariable(char *id, Node *value)
{
  for (int i = 0; i < variable_count; ++i)
  {
    if (strcmp(variables[i].name, id) == 0)
    {
      variables[i].value = value;
      return;
    }
  }
  if (variable_count >= max_variables)
  {
    max_variables *= 2;
    variables = (Variable *)realloc(variables, sizeof(Variable) * max_variables);
  }

  variables[variable_count].name = id;
  variables[variable_count].value = value;
  variable_count += 1;
}

Node *eval(Node *node)
{
  Node *result = NULL;
  switch (node->type)
  {
  case NUMBER_NODE:
    return node;
  case ID_NODE:
    result = getVariable((char *)node->value);
    if (result == NULL)
    {
      printf("Error: variable '%s' is not defined\n", (char *)node->value);
    }
    return result;
  case QUOTED_EXPRESSION_NODE:
    node->type = EXPRESSION_NODE;
    return node;
  case EXPRESSION_NODE:
    return evalExpression(node);
  }
  return result;
}

Node *evalExpression(Node *node)
{
  Node *result = (Node *)malloc(sizeof(Node));
  if (expectExpressionNode(node) != 0 || expectNArguments(node, 1) != 0 || expectIdNode(node->children[0]) != 0)
  {
    return NULL;
  }

  char *function_name = (char *)node->children[0]->value;
  if (strcmp(function_name, "add") == 0)
  {
    if (expectNArguments(node, 3) != 0)
    {
      return NULL;
    }
    double summand = 0;
    Node *value = NULL;
    for (int i = 1; i < node->children_size; ++i)
    {
      value = eval(node->children[i]);
      if (value == NULL || expectNumberNode(value) != 0)
      {
        return NULL;
      }
      summand += ((double *)value->value)[0];
    }

    result->type = NUMBER_NODE;
    result->value = (double *)malloc(sizeof(double));
    ((double *)result->value)[0] = summand;
    result->children = NULL;
    result->children_size = 0;
  }
  else if (strcmp(function_name, "setq") == 0)
  {
    if (expectExactlyNArguments(node, 3) != 0 || expectIdNode(node->children[1]) != 0)
    {
      return NULL;
    }

    char *id = (char *)node->children[1]->value;
    result = eval(node->children[2]);
    if (result != NULL)
    {
      setVariable(id, result);
    }
  }
  else if (strcmp(function_name, "list") == 0)
  {
    if (expectNArguments(node, 1) != 0)
    {
      return NULL;
    }

    result->type = QUOTED_EXPRESSION_NODE;
    result->value = NULL;
    result->children_size = node->children_size - 1;
    result->children = (Node **)malloc(sizeof(Node *) * result->children_size);
    for (int i = 1; i < node->children_size; ++i)
    {
      result->children[i - 1] = eval(node->children[i]);
      if (result->children[i - 1] == NULL)
      {
        return NULL;
      }
    }
  }
  else if (strcmp(function_name, "car") == 0)
  {
    if (expectExactlyNArguments(node, 2) != 0)
    {
      return NULL;
    }

    result = node->children[1]->children[1];
  }
  else if (strcmp(function_name, "cdr") == 0)
  {
    if (expectExactlyNArguments(node, 2) != 0)
    {
      return NULL;
    }

    result->type = QUOTED_EXPRESSION_NODE;
    result->value = NULL;
    result->children_size = node->children[1]->children_size - 2;
    result->children = (Node **)malloc(sizeof(Node *) * result->children_size);
    for (int i = 2; i < node->children[1]->children_size; ++i)
    {
      result->children[i - 2] = node->children[1]->children[i];
    }
  }
  else
  {
    printf("Error: unknown function '%s'\n", function_name);
    return NULL;
  }

  return result;
}
