/**
 * @file   canvas.h
 * @brief  This file contains the function definitions for canvas.c.
 * @author Matthew C. Lindeman
 * @date   April 07, 2023
 * @bug    None known
 * @todo   Nothing
 */
#ifndef CAN_H
#define CAN_H

#include <math.h>
#include <ft2build.h>
#include <png.h>
#include "node.h"
#include FT_FREETYPE_H

#define PPM_HEADER "P3"

typedef struct CANVAS_T {
  pixel ** values;
  int height;
  int width;
} * canvas;

canvas init_canvas(int height, int width, int r, int g, int b);
void debug_canvas(canvas the_canvas);
canvas write_node(canvas the_canvas, node the_node, const char * path_to_font,
    const int font_size);
canvas update_points(canvas the_canvas, node the_node, int x, int y);
canvas connect_node(canvas the_canvas, node parent, node child);
void write_canvas(canvas the_canvas, char * file_name);
void write_canvas_png(canvas the_canvas, char * file_name);
void free_canvas(canvas the_canvas);

#endif
