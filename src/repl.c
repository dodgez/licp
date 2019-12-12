#include "repl.h"

void printTree(Node* node, int tab_size) {
  for (int i = 0; i < tab_size; ++i) {
    printf(" ");
  }
  printf("Type '%s', token '%s', and %d children\n", node->type, node->token, node->children_size);

  for (int i = 0; i < node->children_size; ++i) {
    printTree(node->children[i], tab_size + 2);
  }
}

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
      printTree(&node, 0);
    }
  }
}
