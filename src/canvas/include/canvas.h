#ifndef CAN_H
#define CAN_H

#include <math.h>
#include <ft2build.h>
#include "node.h"
#include FT_FREETYPE_H

#define PPM_HEADER "P3"

typedef struct CANVAS_T {
  pixel ** values;
  int height;
  int width;
} * canvas;

canvas init_canvas(int height, int width);
void debug_canvas(canvas the_canvas);
canvas write_node(canvas the_canvas, node the_node);
canvas update_points(canvas the_canvas, node the_node, int x, int y);
canvas connect_node(canvas the_canvas, node parent, node * children,
    int qty_children);
void write_canvas(canvas the_canvas, char * file_name);
void free_canvas(canvas the_canvas);

#endif
