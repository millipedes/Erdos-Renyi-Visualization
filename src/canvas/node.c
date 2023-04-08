/**
 * @file   node.c
 * @brief  This file contains the funcitons related to the node data structure
 * which is drawn on the canvas.
 * @author Matthew C. Lindeman
 * @date   Arpil 07, 2023
 * @bug    None known
 * @todo   Nothing
 */
#include "include/node.h"

/**
 * This function initializes a node with given name, color, center x coord,
 * center y coord, and the radius.
 * @param      name - The name that will be printed in the node. This is
 * agnostic of language so long as your .ttf supports it.
 * @param     color - The color that the node will be printed in.
 * @param        fx - The center x coordinate.
 * @param        fy - The center y coordinate.
 * @param    radius - The radius of the node (it is a circle).
 * @return the_node - The inited node.
 */
node init_node(char * name, pixel color, int fx, int fy, int radius) {
  node the_node = calloc(1, sizeof(struct NODE_T));
  the_node->name = name;
  the_node->color = color;
  the_node->fx = fx;
  the_node->fy = fy;
  the_node->radius = radius;
  return the_node;
}

/**
 * This function debugs a node.
 * @param the_node - The node to be debugged.
 * @return     N/a
 */
void debug_node(node the_node) {
  printf("[NODE]\n");
  printf("`%s`::(%d, %d) radius: %d\n", the_node->name, the_node->fx,
      the_node->fy, the_node->radius);
  debug_pixel(the_node->color);
}

/**
 * This function frees a node.
 * @param the_node - The node to be freed.
 * @return     N/a
 */
void free_node(node the_node) {
  if(the_node) {
    if(the_node->name)
      free(the_node->name);
    if(the_node->color)
      free_pixel(the_node->color);
    free(the_node);
  }
}
