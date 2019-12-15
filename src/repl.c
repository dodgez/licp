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
      printf("%s\n", error_message);
    } else {
      node = evalExpression(node);
      if (node == NULL) {
        continue;
      }
      if (node->type == NUMBER_NODE) {
        printf("%g\n", ((double*)node->value)[0]);
      }
    }
  }
}
