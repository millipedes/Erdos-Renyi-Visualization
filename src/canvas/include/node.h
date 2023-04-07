#ifndef NODE_H
#define NODE_H

#include <string.h>
#include "../../canvas/include/pixel.h"

#define MAX_NAME_LEN 128

typedef struct NODE_T {
  char * name;
  pixel color;
  int fx;
  int fy;
  int radius;
} * node;

node init_node(char * name, pixel color, int fx, int fy, int radius);
void debug_node(node the_node);
void free_node(node the_node);

#endif
