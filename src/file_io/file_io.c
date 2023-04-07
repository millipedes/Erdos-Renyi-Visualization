#include "include/file_io.h"

g_struct init_gnp(int n, double p) {
  g_struct the_g_struct = calloc(1, sizeof(struct G_STRUCT_T));
  the_g_struct->m_or_p = 'p';
  the_g_struct->n = n;
  the_g_struct->p = p;
  return the_g_struct;
}

g_struct init_gnm(int n, int m) {
  g_struct the_g_struct = calloc(1, sizeof(struct G_STRUCT_T));
  the_g_struct->m_or_p = 'm';
  the_g_struct->n = n;
  the_g_struct->m = m;
  return the_g_struct;
}

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

void free_g_struct(g_struct the_g_struct) {
  if(the_g_struct)
    free(the_g_struct);
}

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
      the_user_params->out_file = parse_file(buf, (int)OUT_FILE_LEN);
    }
    current_index = 0;
  }
  fclose(fp);
  return the_user_params;
}

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
    printf("Path: `%s`\n", the_user_params->out_file);
  printf("Font Size: %d, Canvas Dims: %d\n", the_user_params->font_size,
      the_user_params->canvas_dims);
}

void free_user_params(user_params the_user_params) {
  if(the_user_params) {
    if(the_user_params->node_color)
      free_pixel(the_user_params->node_color);
    if(the_user_params->canvas_color)
      free_pixel(the_user_params->canvas_color);
    if(the_user_params->the_g_struct)
      free_g_struct(the_user_params->the_g_struct);
    if(the_user_params->out_file)
      free(the_user_params->out_file);
    if(the_user_params->path_to_font)
      free(the_user_params->path_to_font);
    free(the_user_params);
  }
}
