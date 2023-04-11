/**
 * @file   file_io.h
 * @brief  This function contains the function definitions and macros for
 * file_io.c.
 * @author Matthew C. Lindeman
 * @date   April 07, 2023
 * @bug    None known
 * @todo   Nothing
 */
#ifndef FIO_H
#define FIO_H

#include <string.h>
#include "../../canvas/include/pixel.h"
#include "../../file_preprocessing/include/file_preprocessing.h"

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
#define GPN          "GNP"
#define GNM          "GNM"
#define OUT_FILE     "OUT_FILE"

#define NODE_COLOR_LEN   strnlen(NODE_COLOR,   MAX_PARAM_SIZE)
#define CANVAS_COLOR_LEN strnlen(CANVAS_COLOR, MAX_PARAM_SIZE)
#define FONT_SIZE_LEN    strnlen(FONT_SIZE,    MAX_PARAM_SIZE)
#define PATH_TO_FONT_LEN strnlen(PATH_TO_FONT, MAX_PARAM_SIZE)
#define CANVAS_DIMS_LEN  strnlen(CANVAS_DIMS,  MAX_PARAM_SIZE)
#define GPN_LEN          strnlen(GPN,          MAX_PARAM_SIZE)
#define GNM_LEN          strnlen(GNM,          MAX_PARAM_SIZE)
#define OUT_FILE_LEN     strnlen(OUT_FILE,     MAX_PARAM_SIZE)

typedef struct G_STRUCT_T {
  double p;
  int n;
  int m;
  char m_or_p;
} * g_struct;

g_struct init_gnp(int n, double p);
g_struct init_gnm(int n, int m);
void debug_g_struct(g_struct the_g_struct);
void free_g_struct(g_struct the_g_struct);

typedef struct USER_PARAMS_T {
  pixel node_color;
  pixel canvas_color;
  g_struct the_g_struct;
  path_wrapper out_file;
  char * path_to_font;
  int font_size;
  int canvas_dims;
} * user_params;

user_params init_user_params(char * config_file);
g_struct parse_g_struct(char * buf, int current_index, char m_or_p);
char * parse_file(char * buf, int current_index);
pixel parse_pixel(char * buf, int current_index);
void debug_user_params(user_params the_user_params);
void free_user_params(user_params the_user_params);

#endif
