#ifndef common_h
#define common_h

#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOOL int
#define TRUE 1
#define FALSE 0

#define NUMBER_NODE 0
#define ID_NODE 1
#define EXPRESSION_NODE 2
#define QUOTED_EXPRESSION_NODE 3

typedef struct _Node {
  int type;
  char* token;
  struct _Node** children;
  int children_size;
} Node;

#endif
