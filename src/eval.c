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
int expectQuotedNode(Node *node)
{
  if (node->type != QUOTED_NODE)
  {
    printf("Error: expected type 'quoted' but got type '%d'\n", node->type);
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
  case QUOTED_NODE:
    return (Node *)node->value;
  case EXPRESSION_NODE:
    return evalExpression(node);
  }
  return result;
}

Node *evalExpression(Node *node)
{
  Node *result = (Node *)malloc(sizeof(Node));
  if (expectExpressionNode(node) != 0 || expectNArguments(node, 1) != 0)
  {
    return NULL;
  }
  if (node->children[0]->type == EXPRESSION_NODE)
  {
    return evalFunction(node, node->children[0]);
  }
  if (expectIdNode(node->children[0]) != 0)
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

    result->type = QUOTED_NODE;
    result->value = malloc(sizeof(Node));
    result->children_size = 0;
    result->children = NULL;
    ((Node *)result->value)->type = EXPRESSION_NODE;
    ((Node *)result->value)->value = NULL;
    ((Node *)result->value)->children_size = node->children_size - 1;
    ((Node *)result->value)->children = (Node **)malloc(sizeof(Node *) * ((Node *)result->value)->children_size);
    for (int i = 1; i < node->children_size; ++i)
    {
      ((Node *)result->value)->children[i - 1] = eval(node->children[i]);
      if (((Node *)result->value)->children[i - 1] == NULL)
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

    if (node->children[1]->type == QUOTED_NODE)
    {
      node = node->children[1];
    }
    else
    {
      node = eval(node->children[1]);
      if (node == NULL || expectQuotedNode(node) != 0)
      {
        return NULL;
      }
    }

    node = (Node *)node->value;
    if (expectExpressionNode(node) != 0 || expectNArguments(node, 1))
    {
      return NULL;
    }
    result = node->children[0];
  }
  else if (strcmp(function_name, "cdr") == 0)
  {
    if (expectExactlyNArguments(node, 2) != 0)
    {
      return NULL;
    }

    if (node->children[1]->type == QUOTED_NODE)
    {
      node = node->children[1];
    }
    else
    {
      node = eval(node->children[1]);
      if (node == NULL || expectQuotedNode(node) != 0)
      {
        return NULL;
      }
    }

    node = (Node *)node->value;
    if (expectExpressionNode(node) != 0 || expectNArguments(node, 1))
    {
      return NULL;
    }
    result->type = QUOTED_NODE;
    result->value = malloc(sizeof(Node));
    result->children_size = 0;
    result->children = NULL;
    ((Node *)result->value)->type = EXPRESSION_NODE;
    ((Node *)result->value)->value = NULL;
    ((Node *)result->value)->children_size = node->children_size - 1;
    ((Node *)result->value)->children = (Node **)malloc(sizeof(Node *) * ((Node *)result->value)->children_size);
    for (int i = 1; i < node->children_size; ++i)
    {
      ((Node *)result->value)->children[i - 1] = node->children[i];
    }
  }
  else if (strcmp(function_name, "lambda") == 0)
  {
    return node;
  }
  else
  {
    Node *function = getVariable(function_name);
    if (function == NULL)
    {
      printf("Error: unknown function '%s'\n", function_name);
      return NULL;
    }
    result = evalFunction(node, function);
  }

  return result;
}

Node *evalFunction(Node *node, Node *function)
{
  Node *result = NULL;

  if (expectExpressionNode(function) != 0 || expectNArguments(function, 3) != 0)
  {
    return NULL;
  }
  if (expectIdNode(function->children[0]) != 0)
  {
    return NULL;
  }
  if (strcmp((char *)function->children[0]->value, "lambda") != 0)
  {
    printf("Error: expected function definition but got '%s'\n", (char*)function->children[0]->value);
    return NULL;
  }
  if (expectExpressionNode(function->children[1]) != 0)
  {
    return NULL;
  }
  if (node->children_size - 1 != function->children[1]->children_size)
  {
    printf("Error: function requires %d arguments but got %d\n", function->children[1]->children_size, node->children_size - 1);
    return NULL;
  }

  for (int i = 0; i < function->children[1]->children_size; ++i)
  {
    Node *child = function->children[1]->children[i];
    if (expectIdNode(child) != 0)
    {
      return NULL;
    }
    setVariable((char *)child->value, eval(node->children[i + 1]));
  }
  for (int i = 2; i < function->children_size; ++i)
  {
    result = eval(function->children[i]);
  }

  return result;
}
