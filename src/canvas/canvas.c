/**
 * @file   canvas.c
 * @brief  This file contains the functions related to the canvas data
 * structure.
 * @author Matthew C. Lindeman
 * @date   April 07, 2023
 * @bug    None known
 * @todo   Nothing
 */
#include "include/canvas.h"

/**
 * This function initializes a function with dimensions heighxwidth.
 * @param      height - The height of the canvas.
 * @param       width - The width of the canvas.
 * @return the_canvas - The inited canvas.
 */
canvas init_canvas(int height, int width, int r, int g, int b) {
  canvas the_canvas = calloc(1, sizeof(struct CANVAS_T));
  the_canvas->height = height;
  the_canvas->width = width;
  the_canvas->values = calloc(height, sizeof(struct PIXEL_T **));
  for(int i = 0; i < height; i++) {
    the_canvas->values[i] = calloc(width, sizeof(struct PIXEL_T *));
    for(int j = 0; j < width; j++)
      the_canvas->values[i][j] = init_pixel(r, g, b);
  }
  return the_canvas;
}

/**
 * This function debugs a canvas.
 * @param the_canvas - The canvas to be debugged.
 * @return       N/a
 */
void debug_canvas(canvas the_canvas) {
  printf("[CANVAS]\n");
  printf("Height: %d Width: %d\n", the_canvas->height, the_canvas->width);
  for(int i = 0; i < the_canvas->height; i++)
    for(int j = 0; j < the_canvas->width; j++)
      debug_pixel(the_canvas->values[i][j]);
}

/**
 * This function uses Bresenham's circle drawing algorithm to draw the nodes.
 * @param   the_canvas - The canvas that the node will be written to.
 * @param     the_node - The node to be drawn.
 * @param path_to_font - The path to the font file.
 * @param    font_size - The size of the font.
 * @return  the_canvas - The canvas with the node written to it.
 */
canvas write_node(canvas the_canvas, node the_node, const char * path_to_font,
    const int font_size) {
  int x = 0;
  int y = the_node->radius;
  int err = 3 - 2 * the_node->radius;
  FT_Library ft;
  FT_Init_FreeType(&ft);
  FT_Face face;
  FT_New_Face(ft, path_to_font, 0, &face);
  FT_Set_Pixel_Sizes(face, 0, font_size);
  int white_len = (int)strnlen(the_node->name, MAX_NAME_LEN);
  // Draw the circle
  update_points(the_canvas, the_node, x, y);
  while(y >= x) {
    x++;
    if(err > 0) {
      y--;
      err += 4 * (x - y) + 10;
    } else
      err += 4 * x + 6;
    update_points(the_canvas, the_node, x, y);
  }
  // Draw the move letters
  for(int i = 0; i < white_len; i++) {
    FT_Load_Char(face, (int)the_node->name[i], FT_LOAD_RENDER);
    FT_GlyphSlot slot = face->glyph;
    int y_min = the_node->fy - (int)((double)slot->bitmap.rows / 2.0);
    int y_max = the_node->fy + (int)((double)slot->bitmap.rows / 2.0);
    int x_min = the_node->fx - (int)((double)slot->bitmap.width / 2.0);
    int x_max = the_node->fx + (int)((double)slot->bitmap.width / 2.0);
    int x_offset = (white_len / 2 - i) * (int)slot->bitmap.width;
    for(int j = y_min; j < y_max; j++)
      for(int k = x_min; k < x_max; k++)
        if(slot->bitmap.buffer[((j - y_min) * (int)slot->bitmap.width)
            + (k - x_min)] > 0) {
          if(j > 0 && j < the_canvas->height
              && (k - x_offset) > 0 && (k - x_offset) < the_canvas->width)
            change_color(the_canvas->values[j][k - x_offset], the_node->color);
        }
  }
  // Free the freetype stuff
  FT_Done_Face(face);
  FT_Done_FreeType(ft);
  return the_canvas;
}

/**
 * This function is used by write_node to write the nodes to the canvas (look up
 * Bresenham's circle drawing algorithm).
 * @param  the_canvas - The canvas that the node will be written to.
 * @param    the_node - The node that is being written to the the canvas.
 * @param           x - The x value that is being written.
 * @param           y - The y value that is being written.
 * @return the_canvas - The canvas that has been written to.
 */
canvas update_points(canvas the_canvas, node the_node, int x, int y) {
  if(y + the_node->fy < the_canvas->height
      && y + the_node->fy > 0
      && x + the_node->fx < the_canvas->width
      && x + the_node->fx > 0)
    change_color(the_canvas->values[ y + the_node->fy][ x + the_node->fx],
        the_node->color);
  if(-y + the_node->fy < the_canvas->height
      && -y + the_node->fy > 0
      && x + the_node->fx < the_canvas->width
      && x + the_node->fx > 0)
    change_color(the_canvas->values[-y + the_node->fy][ x + the_node->fx],
        the_node->color);
  if(y + the_node->fy < the_canvas->height
      && y + the_node->fy > 0
      && -x + the_node->fx < the_canvas->width
      && -x + the_node->fx > 0)
    change_color(the_canvas->values[ y + the_node->fy][-x + the_node->fx],
        the_node->color);
  if(-y + the_node->fy < the_canvas->height
      && -y + the_node->fy > 0
      && -x + the_node->fx < the_canvas->width
      && -x + the_node->fx > 0)
    change_color(the_canvas->values[-y + the_node->fy][-x + the_node->fx],
        the_node->color);
  if(x + the_node->fy < the_canvas->height
      && x + the_node->fy > 0
      && y + the_node->fx < the_canvas->width
      && y + the_node->fx > 0)
    change_color(the_canvas->values[ x + the_node->fy][ y + the_node->fx],
        the_node->color);
  if(-x + the_node->fy < the_canvas->height
      && -x + the_node->fy > 0
      && y + the_node->fx < the_canvas->width
      && y + the_node->fx > 0)
    change_color(the_canvas->values[-x + the_node->fy][ y + the_node->fx],
        the_node->color);
  if(x + the_node->fy < the_canvas->height
      && x + the_node->fy > 0
      && -y + the_node->fx < the_canvas->width
      && -y + the_node->fx > 0)
    change_color(the_canvas->values[ x + the_node->fy][-y + the_node->fx],
        the_node->color);
  if(-x + the_node->fy < the_canvas->height
      && -x + the_node->fy > 0
      && -y + the_node->fx < the_canvas->width
      && -y + the_node->fx > 0)
    change_color(the_canvas->values[-x + the_node->fy][-y + the_node->fx],
        the_node->color);
  return the_canvas;
}

/**
 * This function uses a combination of Bresenham's line drawing algorithm and
 * parametric functions to draw the line quickly.
 * @param
 * @return
 */
canvas connect_node(canvas the_canvas, node parent, node child) {
  double m = 0;
  int b = 0;
  if(parent->fx - child->fx != 0)
    m = ((double)(parent->fy - child->fy)) 
      / ((double)(parent->fx - child->fx));
  else
    m = parent->fx;
  b = parent->fy - m * parent->fx;
  int x_start = 0;
  int x_end = 0;
  if(parent->fx < child->fx) {
    x_start = parent->fx + (parent->radius * -cos(atan2((double)m, -1.0)));
    x_end = child->fx + (child->radius
        * cos(atan2((double)m, -1.0)));
  } else if(parent->fx > child->fx) {
    x_start = parent->fx + (parent->radius * cos(atan2((double)m, -1.0)));
    x_end = child->fx + (child->radius
        * -cos(atan2((double)m, -1.0)));
  }
  if(x_start > x_end) {
    int tmp = x_start;
    x_start = x_end;
    x_end = tmp;
  }
  if(x_start == x_end && parent->fy < child->fy)
    for(int j = parent->fy + parent->radius;
        j < child->fy - child->radius; j++)
      change_color(the_canvas->values[j][parent->fx], parent->color);
  else if(x_start == x_end && parent->fy > child->fy)
    for(int j = child->fy + child->radius;
        j < parent->fy - parent->radius; j++)
      change_color(the_canvas->values[j][parent->fx], parent->color);
  else
    for(int j = x_start; j <= x_end; j++)
      change_color(the_canvas->values[(int)(m * j + b)][j], parent->color);
  return the_canvas;
}

/**
 * This function writes the_canvas to the file specified by file_name.
 * @param the_canvas - The canvas that will be written.
 * @param  file_name - The name of the file to be written.
 * @return       N/a
 */
void write_canvas(canvas the_canvas, char * file_name) {
  FILE * fp = fopen(file_name, "w");
  fprintf(fp, "%s\n", PPM_HEADER);
  fprintf(fp, "%d %d\n", the_canvas->width, the_canvas->height);
  fprintf(fp, "%d\n", MAX_COL);
  for(int i = 0; i < the_canvas->height; i++)
    for(int j = 0; j < the_canvas->width; j++)
      ppm_print(the_canvas->values[i][j], fp);
  fclose(fp);
}

void write_canvas_png(canvas the_canvas, char * file_name) {
  FILE * fp = fopen(file_name, "w");
  png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  png_infop info_ptr = png_create_info_struct(png_ptr);
  png_init_io(png_ptr, fp);
  png_set_IHDR(png_ptr, info_ptr, the_canvas->width, the_canvas->height, 8,
      PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT,
      PNG_FILTER_TYPE_DEFAULT);
  png_write_info(png_ptr, info_ptr);
  for (int i = 0; i < the_canvas->height; i++) {
    png_bytep row = calloc(the_canvas->width * 3, sizeof(png_byte));
    for(int j = 0; j < the_canvas->width; j++) {
      row[3*j + 0] = (png_byte) the_canvas->values[i][j]->r;
      row[3*j + 1] = (png_byte) the_canvas->values[i][j]->g;
      row[3*j + 2] = (png_byte) the_canvas->values[i][j]->b;
    }
    png_write_row(png_ptr, row);
    free(row);
    row = NULL;
  }

  png_write_end(png_ptr, info_ptr);
  png_destroy_write_struct(&png_ptr, &info_ptr);
  fclose(fp);
}

/**
 * This function frees a canvas.
 * @param the_canvas - The canvas to be freed.
 * @return       N/a
 */
void free_canvas(canvas the_canvas) {
  if(the_canvas) {
    if(the_canvas->values) {
      for(int i = 0; i < the_canvas->height; i++) {
        for(int j = 0; j < the_canvas->width; j++)
          free_pixel(the_canvas->values[i][j]);
        free(the_canvas->values[i]);
      }
      free(the_canvas->values);
    }
    free(the_canvas);
  }
}
