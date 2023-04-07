#include "include/erdos_renyi.h"

canvas Gnp(user_params the_user_params) {
  canvas the_canvas = NULL;
  node * graph = NULL;
  int canvas_dims = DEFAULT_CANVAS_DIMS;
  int font_size = DEFAULT_FONT_SIZE;
  char * path_to_font = DEFAULT_PATH_TO_FONT;
  g_struct the_g_struct = DEFAULT_GPN;
  if(the_user_params) {
    if(the_user_params->canvas_dims)
      canvas_dims = the_user_params->canvas_dims;
    if(the_user_params->font_size)
      font_size = the_user_params->font_size;
    if(the_user_params->path_to_font)
      path_to_font = the_user_params->path_to_font;
    if(the_user_params->the_g_struct) {
      free_g_struct(the_g_struct);
      the_g_struct = the_user_params->the_g_struct;
    }
  }
  the_canvas = init_canvas(canvas_dims, canvas_dims);
  graph = make_circular_node_collection(the_canvas, the_g_struct->n,
      path_to_font, font_size, canvas_dims);
  for(int i = 0; i < the_g_struct->n; i++)
    for(int j = 0; j < the_g_struct->n; j++)
      if(i != j)
        if(random_number() <= the_g_struct->p * 100)
          connect_node(the_canvas, graph[i], graph[j]);
  for(int i = 0; i < the_g_struct->n; i++)
    free_node(graph[i]);
  free(graph);
  if(!the_user_params)
    free_g_struct(the_g_struct);
  return the_canvas;
}

canvas Gnm(user_params the_user_params) {
  int current_collection_index = 0;
  int i_rand = 0;
  int j_rand = 0;
  canvas the_canvas = NULL;
  node * graph = NULL;
  int canvas_dims = DEFAULT_CANVAS_DIMS;
  int font_size = DEFAULT_FONT_SIZE;
  char * path_to_font = DEFAULT_PATH_TO_FONT;
  g_struct the_g_struct = DEFAULT_GNM;
  if(the_user_params) {
    if(the_user_params->canvas_dims)
      canvas_dims = the_user_params->canvas_dims;
    if(the_user_params->font_size)
      font_size = the_user_params->font_size;
    if(the_user_params->path_to_font)
      path_to_font = the_user_params->path_to_font;
    if(the_user_params->the_g_struct) {
      free_g_struct(the_g_struct);
      the_g_struct = the_user_params->the_g_struct;
    }
  }
  int tmp = the_g_struct->m;
  int * i_collection = calloc(the_g_struct->m, sizeof(int));
  int * j_collection = calloc(the_g_struct->m, sizeof(int));
  the_canvas = init_canvas(canvas_dims, canvas_dims);
  graph = make_circular_node_collection(the_canvas, the_g_struct->n, path_to_font, font_size,
      canvas_dims);
  while(tmp > 0) {
    i_rand = rand() % the_g_struct->n;
    j_rand = rand() % the_g_struct->n;
    if(i_rand != j_rand
        && not_in_collection(i_collection, i_rand, current_collection_index) != -1
        && not_in_collection(j_collection, j_rand, current_collection_index) != -1) {
      i_collection[current_collection_index] = i_rand;
      j_collection[current_collection_index] = j_rand;
      current_collection_index++;
      tmp--;
    }
  }
  for(int i = 0; i < the_g_struct->m; i++)
    connect_node(the_canvas, graph[i_collection[i]], graph[j_collection[i]]);
  for(int i = 0; i < the_g_struct->n; i++)
    free_node(graph[i]);
  free(graph);
  free(i_collection);
  free(j_collection);
  if(!the_user_params)
    free_g_struct(the_g_struct);
  return the_canvas;
}

node * make_circular_node_collection(canvas the_canvas, int n,
    const char * path_to_font, const int font_size, const int canvas_dims) {
  int central_radius = (int)((double)canvas_dims / 3.0);
  int central_xy = canvas_dims / 2;
  double angle_between_node = 2 * M_PI / (double) n;
  int * x_coords = calloc(n, sizeof(int));
  int * y_coords = calloc(n, sizeof(int));
  for(int i = 0; i < n; i++) {
    x_coords[i] = central_xy + central_radius * cos(angle_between_node * i);
    y_coords[i] = central_xy + central_radius * sin(angle_between_node * i);
  }
  node * graph = calloc(n, sizeof(struct NODE_T *));
  for(int i = 0; i < n; i++) {
    graph[i] = init_node(make_node_name(i + 1), init_pixel(0, 190, 255),
        x_coords[i], y_coords[i], 60);
    write_node(the_canvas, graph[i], path_to_font, font_size);
  }
  free(x_coords);
  free(y_coords);
  return graph;
}

int not_in_collection(int * collection, int value, int index) {
  for(int i = 0; i < index; i++)
    if(collection[i] == value)
      return -1;
  return 1;
}

char * make_node_name(int i) {
  int name_len = snprintf(NULL, 0, "%d", i) + 1;
  char * name = calloc(name_len + 1, sizeof(char));
  name[0] = NAME_CHAR;
  snprintf(name + 1, name_len, "%d", i);
  return name;
}

int random_number(void) {
  return rand() % 100;
}
