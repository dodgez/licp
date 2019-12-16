#include "main.h"

int main(int argc, char **argv)
{
  error_message = NULL;
  max_variables = 1;
  variable_count = 0;
  variables = (Variable *)malloc(sizeof(Variable) * max_variables);

  if (argc > 1)
  {
    char *line = NULL;
    FILE *file = NULL;
    Node *node = NULL;
    size_t length = 0;
    size_t read = 0;
    for (int i = 1; i < argc; ++i)
    {
      file = fopen(argv[i], "r");
      if (file == NULL)
      {
        printf("Error: could not open file '%s'\n", argv[i]);
        continue;
      }

      while ((read = getline(&line, &length, file)) != -1)
      {
        node = parseExpression(getStreamFromString(line));
        if (node == NULL)
        {
          printf("%s\n", error_message);
        }
        else
        {
          evalExpression(node);
        }
      }
      fclose(file);
    }
    if (line)
    {
      free(line);
    }
  }
  repl();

  return 0;
}
