#ifndef FIO_H
#define FIO_H

#include <string.h>
#include "../../canvas/include/pixel.h"

#define MAX_PARAM_SIZE       64
#define MAX_CONFIG_LINE_SIZE 512

#define IS_WHITESPACE(c) ((c == 't') || (c == ' '))
#define IS_COMMA(c) (c == ',')
#define IS_QUOTE(c) ((c == '\'') || (c == '\"'))

#define NODE_COLOR   "NODE_COLOR"
#define CANVAS_COLOR "CANVAS_COLOR"
#define FONT_SIZE    "FONT_SIZE"
#define PATH_TO_FONT "PATH_TO_FONT"
#define CANVAS_DIMS  "CANVAS_DIMS"

#define NODE_COLOR_LEN   strnlen("NODE_COLOR", MAX_PARAM_SIZE)
#define CANVAS_COLOR_LEN strnlen("CANVAS_COLOR", MAX_PARAM_SIZE)
#define FONT_SIZE_LEN    strnlen("FONT_SIZE", MAX_PARAM_SIZE)
#define PATH_TO_FONT_LEN strnlen("PATH_TO_FONT", MAX_PARAM_SIZE)
#define CANVAS_DIMS_LEN  strnlen("CANVAS_DIMS", MAX_PARAM_SIZE)

typedef struct USER_PARAMS_T {
  pixel node_color;
  pixel canvas_color;
  char * path_to_font;
  int font_size;
  int canvas_dims;
} * user_params;

user_params init_user_params(char * config_file);
pixel get_pixel(char * buf, int current_index);
void debug_user_params(user_params the_user_params);
void free_user_params(user_params the_user_params);

#endif
