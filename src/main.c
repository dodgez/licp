#include "main.h"

int main(int argc, char** argv) {
  variables = (Var*)malloc(sizeof(Var) * 1);
  variable_count = 0;
  allocated_variables = 1;

  if (argc > 1) {
    char* line = NULL;
    FILE* file = NULL;
    Node* node = NULL;
    size_t length = 0;
    size_t read = 0;
    for (int i = 1; i < argc; ++i) {
      file = fopen(argv[i], "r");
      if (file == NULL) {
        printf("Error: could not open file '%s'\n", argv[i]);
      }

      while ((read = getline(&line, &length, file)) != -1) {
        node = parseExpression(getStreamFromString(line));
        if (node == NULL) {
          printf(error_message);
        } else {
          Value* result = eval(node);
          printf("Variables defined: %d\n", variable_count);
        }
      }
      fclose(file);
    }
    if (line) {
      free(line);
    }
  }
  repl();

  return 0;
}
