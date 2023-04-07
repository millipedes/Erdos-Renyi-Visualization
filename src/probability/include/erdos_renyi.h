#ifndef ERD_H
#define ERD_H

#include "../../file_io/include/file_io.h"
#include "../../canvas/include/canvas.h"

#define DEFAULT_NODE_COLOR   init_pixel(0, 190, 255)
#define DEFAULT_CANVAS_COLOR init_pixel(0, 0, 0)
#define DEFAULT_FONT_SIZE    24
#define DEFAULT_PATH_TO_FONT "fonts/FiraCode-Bold.ttf"
#define DEFAULT_CANVAS_DIMS  2000
#define DEFAULT_GPN          init_gnp(30, 1.0)
#define DEFAULT_GNM          init_gnm(15, 10)
#define DEFAULT_OUT_FILE     "test.ppm"

#define NAME_CHAR 'n'

canvas Gnp(user_params the_user_params);
canvas Gnm(user_params the_user_params);
node * make_circular_node_collection(canvas the_canvas, int n,
    const char * path_to_font, const int font_size, const int canvas_dims);
char * make_node_name(int i);
int not_in_collection(int * collection, int value, int index);
int random_number(void);

#endif
