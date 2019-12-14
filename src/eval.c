#include "eval.h"

Value* getValueFromNode(Node* node) {
  Value* value = (Value*)malloc(sizeof(Value));
  if (node->type == NUMBER_NODE) {
    value->type = NUMBER_VALUE;
    value->data = malloc(sizeof(double));
    ((double*)value->data)[0] = atof(node->token);
  } else if (node->type == EXPRESSION_NODE) {
    value = eval(node);
    if (value == NULL) {
      return NULL;
    }
  } else {
    printf("Error: node type %d not supported\n", value->type);
    return NULL;
  }
  return value;
}

int expectNArguments(Node* node, int n) {
  if (node->children_size < n) {
    printf("Error: expected function to have at least %d arguments but got %d\n", n, node->children_size);
    return 1;
  }

  return 0;
}

void addVariable(Var* variable) {
  if (variable_count >= allocated_variables) {
    allocated_variables *= 2;
    variables = (Var*)realloc(variables, sizeof(Var) * allocated_variables);
  }

  variables[variable_count] = *variable;
  variable_count += 1;
}

Var* getVariable(char* name) {
  Var* result = (Var*)malloc(sizeof(Var));
  for (int i = 0; i < variable_count; ++i) {
    if (strcmp(variables[i].name, name) == 0) {
      result->name = variables[i].name;
      result->data = variables[i].data;
      return result;
    }
  }
  return NULL;
}

Value* eval(Node* node) {
  Value* result = (Value*)malloc(sizeof(Value));
  if (node->type != EXPRESSION_NODE) {
    printf("Error: expected 'expression' but got '%s'\n", node->type);
    return NULL;
  }
  if (node->children_size == 0) {
    printf("Error: expected expression to have at least 1 argument\n");
    return NULL;
  }
  
  Node* function = node->children[0];
  if (function->type != ID_NODE) {
    printf("Error: invalid function id '%s'\n", function->token);
    return NULL;
  }

  char* function_name = function->token;
  if (strcmp(function_name, "add") == 0) {
    if (expectNArguments(node, 3) != 0) {
      return NULL;
    }
    Value* value1 = getValueFromNode(node->children[1]);
    Value* value2 = getValueFromNode(node->children[2]);
    if (value1 == NULL || value2 == NULL) {
      return NULL;
    }

    result->type = NUMBER_VALUE;
    result->data = malloc(sizeof(double));
    ((double*)result->data)[0] = ((double*)value1->data)[0] + ((double*)value2->data)[0];
  } else if (strcmp(function_name, "setq") == 0) {
    if (expectNArguments(node, 3) != 0) {
      return NULL;
    }
    if (node->children[1]->type != ID_NODE) {
      printf("Error: expected identifier but got %d\n", node->children[1]->type);
      return NULL;
    }
    Var* variable = getVariable(node->children[1]->token);
    Value* value = getValueFromNode(node->children[2]);
    if (value == NULL) {
      return NULL;
    }
    if (variable == NULL) {
      variable = (Var*)malloc(sizeof(Var));
      variable->name = node->children[1]->token;
      variable->data = value;
      addVariable(variable);
    } else {
      variable->data = value;
    }
    result = variable->data;
  } else {
    printf("Error: unknown function '%s'\n", function_name);
    return NULL;
  }

  return result;
}
