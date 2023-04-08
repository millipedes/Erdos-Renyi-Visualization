/**
 * @file   pixel.h
 * @brief  This file contains the function definitions for pixel.c.
 * @author Matthew C. Lindeman
 * @date   Arpil 07, 2023
 * @bug    None known
 * @todo   Nothing
 */
#ifndef PIX_H
#define PIX_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_COL 255
#define MIN_COL 0

typedef struct PIXEL_T {
  int r;
  int g;
  int b;
} * pixel;

pixel init_pixel(int r, int g, int b);
pixel change_color(pixel dest, pixel src);
void debug_pixel(pixel the_pixel);
void ppm_print(pixel the_pixel, FILE * fp);
void free_pixel(pixel the_pixel);

#endif
