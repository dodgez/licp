#include "repl.h"

void repl(void) {
  Node node;
  char* input = NULL;
  size_t size;
  while (TRUE) {
    printf(">");
    getline(&input, &size, stdin);
    if (parseExpression(getStreamFromString(input), &node) != 0) {
      printf(error_message);
    } else {
      Value result;
      eval(&node, &result);

      if (result.type == NUMBER_VALUE) {
        printf("%d\n", ((int*)result.data)[0]);
      }
    }
  }
}
