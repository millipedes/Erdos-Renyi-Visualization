#include "include/node.h"

node init_node(move the_move, pixel color, int fx, int fy, int radius) {
  node the_node = calloc(1, sizeof(struct NODE_T));
  the_node->the_move = the_move;
  the_node->color = color;
  the_node->fx = fx;
  the_node->fy = fy;
  the_node->radius = radius;
  return the_node;
}

void debug_node(node the_node) {
  printf("[NODE]\n");
  debug_move(the_node->the_move);
  debug_pixel(the_node->color);
  printf("(%d, %d) radius: %d\n", the_node->fx, the_node->fy, the_node->radius);
}

void free_node(node the_node) {
  if(the_node) {
    if(the_node->the_move)
      free_move(the_node->the_move);
    if(the_node->color)
      free_pixel(the_node->color);
    free(the_node);
  }
}
