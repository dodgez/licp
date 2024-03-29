#include "main.h"

int main(int argc, char **argv)
{
  error_message = NULL;
  variables = NULL;

  if (argc > 1)
  {
    char *line = NULL;
    char *output = NULL;
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
        node = parseAny(getStreamFromString(line));
        if (node == NULL)
        {
          printf("%s\n", error_message);
        }
        else
        {
          node = eval(node);
          if (node != NULL)
          {
            output = sprintNode(node);
            if (output != NULL)
            {
              printf("%s\n", output);
            }
          }
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
