#ifndef common_h
#define common_h

#include <ctype.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOOL int
#define TRUE 1
#define FALSE 0

#define NUMBER_NODE 0
#define BOOLEAN_NODE 1
#define ID_NODE 2
#define EXPRESSION_NODE 3
#define QUOTED_NODE 4

typedef struct Node
{
  int type;
  void *value;
  int children_size;
  struct Node **children;
} Node;

#endif
