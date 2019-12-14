#include "eval.h"

int getNumberFromValue(Value* value, double* ret) {
  if (value->type != NUMBER_VALUE) {
    printf("Error: expected numeric value but got %d\n", value->type);
    return 1;
  }

  ret[0] = *((double*)value->data);
  return 0;
}

int getValueFromNode(Node* node, Value* value) {
  if (node->type == NUMBER_NODE) {
    value->type = NUMBER_VALUE;
    value->data = malloc(sizeof(double));

    ((double*)value->data)[0] = atof(node->token);
  } else if (node->type == EXPRESSION_NODE) {
    if (eval(node, value) != 0) {
      return 1;
    }
  } else {
    printf("Error: node type %d not supported\n", value->type);
    return 1;
  }

  return 0;
}

int expectNArguments(Node* node, int n) {
  if (node->children_size < n) {
    printf("Error: expected function to have at least %d arguments but got %d\n", n, node->children_size);
    return 1;
  }

  return 0;
}

int eval(Node* node, Value* result) {
  if (node->type != EXPRESSION_NODE) {
    printf("Error: expected 'expression' but got '%s'\n", node->type);
    return 1;
  }

  if (node->children_size == 0) {
    printf("Error: expected expression to have at least 1 argument\n");
    return 1;
  }
  
  Node* function = node->children[0];

  if (function->type != ID_NODE) {
    printf("Error: invalid function id '%s'\n", function->token);
    return 1;
  }

  char* function_name = function->token;
  if (strcmp(function_name, "add") == 0) {
    if (expectNArguments(node, 3) != 0) {
      return 1;
    }

    Value value1;
    Value value2;

    if (getValueFromNode(node->children[1], &value1) != 0) {
      return 1;
    }
    if (getValueFromNode(node->children[2], &value2) != 0) {
      return 1;
    }

    result->type = NUMBER_VALUE;
    result->data = malloc(sizeof(double));
    ((double*)result->data)[0] = ((double*)value1.data)[0] + ((double*)value2.data)[0];
  } else if (strcmp(function_name, "sub") == 0) {
    if (expectNArguments(node, 3) != 0) {
      return 1;
    }

    Value value1;
    Value value2;

    if (getValueFromNode(node->children[1], &value1) != 0) {
      return 1;
    }
    if (getValueFromNode(node->children[2], &value2) != 0) {
      return 1;
    }

    result->type = NUMBER_VALUE;
    result->data = malloc(sizeof(double));
    ((double*)result->data)[0] = ((double*)value1.data)[0] - ((double*)value2.data)[0];
  } else if (strcmp(function_name, "mul") == 0) {
    if (expectNArguments(node, 3) != 0) {
      return 1;
    }

    Value value1;
    Value value2;

    if (getValueFromNode(node->children[1], &value1) != 0) {
      return 1;
    }
    if (getValueFromNode(node->children[2], &value2) != 0) {
      return 1;
    }

    result->type = NUMBER_VALUE;
    result->data = malloc(sizeof(double));
    ((double*)result->data)[0] = ((double*)value1.data)[0] * ((double*)value2.data)[0];
  } else if (strcmp(function_name, "div") == 0) {
    if (expectNArguments(node, 3) != 0) {
      return 1;
    }

    Value value1;
    Value value2;

    if (getValueFromNode(node->children[1], &value1) != 0) {
      return 1;
    }
    if (getValueFromNode(node->children[2], &value2) != 0) {
      return 1;
    }

    result->type = NUMBER_VALUE;
    result->data = malloc(sizeof(double));
    ((double*)result->data)[0] = ((double*)value1.data)[0] / ((double*)value2.data)[0];
  } else if (strcmp(function_name, "pow") == 0) {
    if (expectNArguments(node, 3) != 0) {
      return 1;
    }

    Value value1;
    Value value2;

    if (getValueFromNode(node->children[1], &value1) != 0) {
      return 1;
    }
    if (getValueFromNode(node->children[2], &value2) != 0) {
      return 1;
    }

    result->type = NUMBER_VALUE;
    result->data = malloc(sizeof(double));
    ((double*)result->data)[0] = pow(((double*)value1.data)[0], ((double*)value2.data)[0]);
  } else {
    printf("Error: unknown function '%s'\n", function_name);
    return 1;
  }

  return 0;
}
