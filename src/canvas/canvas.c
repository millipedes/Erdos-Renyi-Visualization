#include "include/canvas.h"

canvas init_canvas(int height, int width) {
  canvas the_canvas = calloc(1, sizeof(struct CANVAS_T));
  the_canvas->height = height;
  the_canvas->width = width;
  the_canvas->values = calloc(height, sizeof(struct PIXEL_T **));
  for(int i = 0; i < height; i++) {
    the_canvas->values[i] = calloc(width, sizeof(struct PIXEL_T *));
    for(int j = 0; j < width; j++)
      the_canvas->values[i][j] = init_pixel(MIN_COL, MIN_COL, MIN_COL);
  }
  return the_canvas;
}

void debug_canvas(canvas the_canvas) {
  printf("[CANVAS]\n");
  printf("Height: %d Width: %d\n", the_canvas->height, the_canvas->width);
  for(int i = 0; i < the_canvas->height; i++)
    for(int j = 0; j < the_canvas->width; j++)
      debug_pixel(the_canvas->values[i][j]);
}

/**
 * This function uses Bresenham's circle drawing algorithm to draw the nodes.
 * @param
 * @return
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
