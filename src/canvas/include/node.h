#ifndef NODE_H
#define NODE_H

#include "../../canvas/include/pixel.h"
#include "../../move/include/move.h"

typedef struct NODE_T {
  move the_move;
  pixel color;
  int fx;
  int fy;
  int radius;
} * node;

node init_node(move the_move, pixel color, int fx, int fy, int radius);
void debug_node(node the_node);
void free_node(node the_node);

#endif
