#include "repl.h"

void repl(void) {
  Node* node;
  char* input = NULL;
  size_t size = 0;
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
    }
  }
}
