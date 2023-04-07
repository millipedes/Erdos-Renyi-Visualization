#include "include/pixel.h"

pixel init_pixel(int r, int g, int b) {
  pixel the_pixel = calloc(1, sizeof(struct PIXEL_T));
  the_pixel->r = r;
  the_pixel->g = g;
  the_pixel->b = b;
  return the_pixel;
}

pixel change_color(pixel dest, pixel src) {
  dest->r = src->r;
  dest->g = src->g;
  dest->b = src->b;
  return dest;
}

void debug_pixel(pixel the_pixel) {
  printf("[PIXEL]\n");
  printf("(%d, %d, %d)\n", the_pixel->r, the_pixel->g, the_pixel->b);
}

void ppm_print(pixel the_pixel, FILE * fp) {
  fprintf(fp, "%d %d %d\n", the_pixel->r, the_pixel->g, the_pixel->b);
}

void free_pixel(pixel the_pixel) {
  if(the_pixel)
    free(the_pixel);
}
