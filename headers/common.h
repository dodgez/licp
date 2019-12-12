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

typedef struct _Node {
  char* type;
  char* token;
  struct _Node** children;
  int children_size;
} Node;

#endif
