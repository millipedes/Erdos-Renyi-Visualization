#include "include/node.h"

node init_node(char * name, pixel color, int fx, int fy, int radius) {
  node the_node = calloc(1, sizeof(struct NODE_T));
  the_node->name = name;
  the_node->color = color;
  the_node->fx = fx;
  the_node->fy = fy;
  the_node->radius = radius;
  return the_node;
}

void debug_node(node the_node) {
  printf("[NODE]\n");
  printf("`%s`::(%d, %d) radius: %d\n", the_node->name, the_node->fx,
      the_node->fy, the_node->radius);
  debug_pixel(the_node->color);
}

void free_node(node the_node) {
  if(the_node) {
    if(the_node->name)
      free(the_node->name);
    if(the_node->color)
      free_pixel(the_node->color);
    free(the_node);
  }
}
