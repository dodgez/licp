#include "repl.h"

char *sprintNode(Node *node)
{
  if (node == NULL)
  {
    return "nil";
  }
  char *result = (char *)malloc(sizeof(char) * MAX_SPRINTNODE_LENGTH);
  memset(result, 0, sizeof(char) * MAX_SPRINTNODE_LENGTH);
  int index = 1;
  switch (node->type)
  {
  case NUMBER_NODE:
    snprintf(result, MAX_SPRINTNODE_LENGTH, "%g", ((double *)node->value)[0]);
    break;
  case BOOLEAN_NODE:
    snprintf(result, MAX_SPRINTNODE_LENGTH, "%s", ((int *)node->value)[0] == 1 ? "true" : "false");
    break;
  case ID_NODE:
    snprintf(result, MAX_SPRINTNODE_LENGTH, "%s", (char *)node->value);
    break;
  case QUOTED_NODE:
    return sprintNode((Node *)node->value);
  case EXPRESSION_NODE:
    sprintf(result, "(");
    char *text = NULL;
    int length = 0;
    for (int i = 0; i < node->children_size; ++i)
    {
      text = sprintNode(node->children[i]);
      length = strlen(text);
      snprintf(result + index, MAX_SPRINTNODE_LENGTH - index, i == 0 ? "%s" : " %s", text);
      length = (i == 0) ? length : length + 1;
      if (index + length > MAX_SPRINTNODE_LENGTH - 1)
      {
        sprintf(result + MAX_SPRINTNODE_LENGTH - 4, "...");
        index = MAX_SPRINTNODE_LENGTH - 1;
        break;
      }
      else
      {
        index += length;
      }
    }

    sprintf(result + index, ")");
    break;
  }
  return result;
}

void repl(void)
{
  Node *node = NULL;
  char *input = NULL;
  size_t size = 0;
  char *output = NULL;
  while (TRUE)
  {
    printf(">");
    getline(&input, &size, stdin);
    node = parseAny(getStreamFromString(input));
    if (node == NULL)
    {
      printf("%s\n", error_message);
    }
    else
    {
      node = eval(node);
      output = sprintNode(node);
      if (output != NULL)
      {
        printf("%s\n", output);
      }
    }
  }
}
