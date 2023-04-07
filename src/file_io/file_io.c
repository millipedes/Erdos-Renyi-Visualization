#include "include/file_io.h"

user_params init_user_params(char * config_file) {
  FILE * fp = fopen(config_file, "r");
  user_params the_user_params = calloc(1, sizeof(struct USER_PARAMS_T));
  the_user_params->node_color = NULL;
  the_user_params->canvas_color = NULL;
  the_user_params->path_to_font = NULL;
  the_user_params->font_size = 0;
  the_user_params->canvas_dims = 0;
  char buf[MAX_CONFIG_LINE_SIZE] = {0};
  int current_index = 0;
  while(fgets(buf, MAX_CONFIG_LINE_SIZE, fp)) {
    if(!strncmp(NODE_COLOR, buf, NODE_COLOR_LEN)) {
      the_user_params->node_color = get_pixel(buf, (int)NODE_COLOR_LEN);
    } else if(!strncmp(CANVAS_COLOR, buf, CANVAS_COLOR_LEN)) {
      the_user_params->canvas_color = get_pixel(buf, (int)CANVAS_COLOR_LEN);
    } else if(!strncmp(FONT_SIZE, buf, FONT_SIZE_LEN)) {
      current_index = (int)FONT_SIZE_LEN;
      while(!IS_WHITESPACE(buf[current_index])) current_index++;
      the_user_params->font_size = atoi(buf + current_index);
    } else if(!strncmp(PATH_TO_FONT, buf, PATH_TO_FONT_LEN)) {
      int path_start = 0;
      current_index = (int)PATH_TO_FONT_LEN;
      while(!IS_QUOTE(buf[current_index])) current_index++;
      // The quote itself
      current_index++;
      path_start = current_index;
      while(!IS_QUOTE(buf[current_index])) current_index++;
      int path_len = (current_index - path_start) + 1;
      the_user_params->path_to_font = calloc(path_len, sizeof(char));
      strncpy(the_user_params->path_to_font, buf + path_start, path_len - 1);
    } else if(!strncmp(CANVAS_DIMS, buf, CANVAS_DIMS_LEN)) {
      current_index = (int)CANVAS_DIMS_LEN;
      while(!IS_WHITESPACE(buf[current_index])) current_index++;
      the_user_params->canvas_dims = atoi(buf + current_index);
    }
    current_index = 0;
  }
  fclose(fp);
  return the_user_params;
}

pixel get_pixel(char * buf, int current_index) {
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
  if(the_user_params->path_to_font)
    printf("Path: `%s`\n", the_user_params->path_to_font);
  printf("Font Size: %d, Canvas Dims: %d\n", the_user_params->font_size,
      the_user_params->canvas_dims);
}

void free_user_params(user_params the_user_params) {
  if(the_user_params) {
    if(the_user_params->node_color)
      free_pixel(the_user_params->node_color);
    if(the_user_params->canvas_color)
      free_pixel(the_user_params->canvas_color);
    if(the_user_params->path_to_font)
      free(the_user_params->path_to_font);
    free(the_user_params);
  }
}
