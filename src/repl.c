#include "repl.h"

void repl(void) {
  Node* node;
  char* input = NULL;
  size_t size;
  variables = (Var*)malloc(sizeof(Var) * 1);
  variable_count = 0;
  allocated_variables = 1;
  while (TRUE) {
    printf(">");
    getline(&input, &size, stdin);
    node = parseExpression(getStreamFromString(input));
    if (node == NULL) {
      printf(error_message);
    } else {
      Value* result = eval(node);
      if (result == NULL) {
        continue;
      }
      if (result->type == NUMBER_VALUE) {
        printf("%g\n", ((double*)result->data)[0]);
      }

      for (int i = 0; i < variable_count; ++i) {
        printf("Variable '%s' with value type %d\n", variables[i].name, variables[i].data->type);
      }
    }
  }
}
