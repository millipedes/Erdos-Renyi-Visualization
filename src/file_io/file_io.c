/**
 * @file   file_io.c
 * @brief  This function contains all of the functions related to file io and
 * the data structures g_struct (what variation of the Erdos Renyi RGT) is being
 * written and the user_params data struct (i.e. parameters the user can tweak).
 * @author Matthew C. Lindeman
 * @date   April 07, 2023
 * @bug    None known
 * @todo   Nothing
 */
#include "include/file_io.h"

/**
 * This function initializes a g_struct (GNP) data structure.
 * @param             n - The n parameter.
 * @param             p - The p parameter.
 * @return the_g_struct - The inited g struct.
 */
g_struct init_gnp(int n, double p) {
  g_struct the_g_struct = calloc(1, sizeof(struct G_STRUCT_T));
  the_g_struct->m_or_p = 'p';
  the_g_struct->n = n;
  the_g_struct->p = p;
  return the_g_struct;
}

/**
 * This function initializes a g_struct (GNM) data structure.
 * @param             n - The n parameter.
 * @param             m - The m parameter.
 * @return the_g_struct - The inited g struct.
 */
g_struct init_gnm(int n, int m) {
  g_struct the_g_struct = calloc(1, sizeof(struct G_STRUCT_T));
  the_g_struct->m_or_p = 'm';
  the_g_struct->n = n;
  the_g_struct->m = m;
  return the_g_struct;
}

/**
 * This function debugs a g_struct.
 * @param the_g_struct - the g_struct to be debugged.
 * @return         N/a
 */
void debug_g_struct(g_struct the_g_struct) {
  switch(the_g_struct->m_or_p) {
    case 'm':
      printf("[G_STRUCT]: n: %d m: %d\n", the_g_struct->n, the_g_struct->m);
      break;
    case 'p':
      printf("[G_STRUCT]: n: %d p: %f\n", the_g_struct->n, the_g_struct->p);
      break;
  }
}

/**
 * This function frees a g_struct.
 * @param the_g_struct - the g_struct to be freed.
 * @return         N/a
 */
void free_g_struct(g_struct the_g_struct) {
  if(the_g_struct)
    free(the_g_struct);
}

/**
 * This function initializes the user_params data struct from the given config
 * file, see the docs for more info on the config file.
 * @param      config_file - The path to the config file.
 * @return the_user_params - The inited user params.
 */
user_params init_user_params(char * config_file) {
  FILE * fp = fopen(config_file, "r");
  user_params the_user_params = calloc(1, sizeof(struct USER_PARAMS_T));
  the_user_params->node_color = NULL;
  the_user_params->canvas_color = NULL;
  the_user_params->path_to_font = NULL;
  the_user_params->the_g_struct = NULL;
  the_user_params->font_size = 0;
  the_user_params->canvas_dims = 0;
  char buf[MAX_CONFIG_LINE_SIZE] = {0};
  int current_index = 0;
  while(fgets(buf, MAX_CONFIG_LINE_SIZE, fp)) {
    if(!strncmp(NODE_COLOR, buf, NODE_COLOR_LEN)) {
      the_user_params->node_color = parse_pixel(buf, (int)NODE_COLOR_LEN);
    } else if(!strncmp(CANVAS_COLOR, buf, CANVAS_COLOR_LEN)) {
      the_user_params->canvas_color = parse_pixel(buf, (int)CANVAS_COLOR_LEN);
    } else if(!strncmp(FONT_SIZE, buf, FONT_SIZE_LEN)) {
      current_index = (int)FONT_SIZE_LEN;
      while(!IS_WHITESPACE(buf[current_index])) current_index++;
      the_user_params->font_size = atoi(buf + current_index);
    } else if(!strncmp(PATH_TO_FONT, buf, PATH_TO_FONT_LEN)) {
      the_user_params->path_to_font = parse_file(buf, (int)PATH_TO_FONT_LEN);
    } else if(!strncmp(CANVAS_DIMS, buf, CANVAS_DIMS_LEN)) {
      current_index = (int)CANVAS_DIMS_LEN;
      while(!IS_WHITESPACE(buf[current_index])) current_index++;
      the_user_params->canvas_dims = atoi(buf + current_index);
    } else if(!strncmp(GPN, buf, GPN_LEN)) {
      if(the_user_params->the_g_struct)
        fprintf(stderr, "[INIT_USER_PARAMS]: Already inited GNM/GNP\n");
      else
        the_user_params->the_g_struct = parse_g_struct(buf, GPN_LEN, 'p');
    } else if(!strncmp(GNM, buf, GNM_LEN)) {
      if(the_user_params->the_g_struct)
        fprintf(stderr, "[INIT_USER_PARAMS]: Already inited GNM/GNP\n");
      else
        the_user_params->the_g_struct = parse_g_struct(buf, GNM_LEN, 'm');
    } else if(!strncmp(OUT_FILE, buf, OUT_FILE_LEN)) {
      char * out_file = parse_file(buf, (int)OUT_FILE_LEN);
      the_user_params->out_file = init_path_wrapper(out_file);
      free(out_file);
    }
    current_index = 0;
  }
  fclose(fp);
  return the_user_params;
}

/**
 * This function parses a g struct and assigns parameters appropriately.
 * @param           buf - The buffer from which the g_struct is being parsed.
 * @param current_index - The current_index of the buffer being parsed.
 * @param        m_or_p - If it is GNP or GNM.
 * @return           .\ - The g inited struct.
 */
g_struct parse_g_struct(char * buf, int current_index, char m_or_p) {
  while(!IS_WHITESPACE(buf[current_index])) current_index++;
  int n = 0;
  switch(m_or_p) {
    case 'm':
      n = atoi(buf + current_index);
      while(!IS_COMMA(buf[current_index])) current_index++;
      // The comma itself
      current_index++;
      int m = atoi(buf + current_index);
      return init_gnm(n, m);
    case 'p':
      n = atoi(buf + current_index);
      while(!IS_COMMA(buf[current_index])) current_index++;
      // The comma itself
      current_index++;
      double p = atof(buf + current_index);
      return init_gnp(n, p);
  }
  fprintf(stderr, "[PARSE_G_sTRUCT]: Error Parsing G Variation\n");
  return NULL;
}

/**
 * This function parses a file (output or font).
 * @param           buf - The buffer from which the file is being parsed.
 * @param current_index - The current_index of the buffer being parsed.
 * @return         path - The file name.
 */
char * parse_file(char * buf, int current_index) {
  char * path = NULL;
  int path_start = 0;
  while(!IS_QUOTE(buf[current_index])) current_index++;
  // The quote itself
  current_index++;
  path_start = current_index;
  while(!IS_QUOTE(buf[current_index])) current_index++;
  int path_len = (current_index - path_start) + 1;
  path = calloc(path_len, sizeof(char));
  strncpy(path, buf + path_start, path_len - 1);
  return path;
}

/**
 * This function parses a pixel struct and assigns parameters appropriately.
 * @param           buf - The buffer from which the pixel is being parsed.
 * @param current_index - The current_index of the buffer being parsed.
 * @return           .\ - The inited pixel struct.
 */
pixel parse_pixel(char * buf, int current_index) {
  while(!IS_WHITESPACE(buf[current_index])) current_index++;
  int r = atoi(buf + current_index);
  while(!IS_COMMA(buf[current_index])) current_index++;
  // The comma itself
  current_index++;
  int g = atoi(buf + current_index);
  while(!IS_COMMA(buf[current_index])) current_index++;
  // The comma itself
  current_index++;
  int b = atoi(buf + current_index);
  return init_pixel(r, g, b);
}

/**
 * This function debugs a user_params data structure.
 * @param the_user_params - The user_params data structure to be debugged.
 * @return           N/a
 */
void debug_user_params(user_params the_user_params) {
  printf("[USER_PARAMS]\n");
  if(the_user_params->node_color)
    debug_pixel(the_user_params->node_color);
  if(the_user_params->canvas_color)
    debug_pixel(the_user_params->canvas_color);
  if(the_user_params->the_g_struct)
    debug_g_struct(the_user_params->the_g_struct);
  if(the_user_params->path_to_font)
    printf("Path: `%s`\n", the_user_params->path_to_font);
  if(the_user_params->out_file)
    debug_path_wrapper(the_user_params->out_file);
  printf("Font Size: %d, Canvas Dims: %d\n", the_user_params->font_size,
      the_user_params->canvas_dims);
}

/**
 * This function frees a user_params data structure.
 * @param the_user_params - The user_params data structure to be freed.
 * @return           N/a
 */
void free_user_params(user_params the_user_params) {
  if(the_user_params) {
    if(the_user_params->node_color)
      free_pixel(the_user_params->node_color);
    if(the_user_params->canvas_color)
      free_pixel(the_user_params->canvas_color);
    if(the_user_params->the_g_struct)
      free_g_struct(the_user_params->the_g_struct);
    if(the_user_params->out_file)
      free_path_wrapper(the_user_params->out_file);
    if(the_user_params->path_to_font)
      free(the_user_params->path_to_font);
    free(the_user_params);
  }
}
