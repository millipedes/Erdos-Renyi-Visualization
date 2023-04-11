/**
 * @file   canvas.c
 * @brief  This file contains those functions which are related to executing the
 * GNP and GNM variations of the erdos_renyi RGT.
 * @author Matthew C. Lindeman
 * @date   Arpil 07, 2023
 * @bug    None known
 * @todo   Nothing
 */
#include "include/erdos_renyi.h"

/**
 * This function executed the GNP variation (if any user parameter is not
 * specified or NULL is sent to this function it will fallback on the defaults).
 * @param the_user_params - The user paramters that were specified.
 * @return     the_canvas - The canvas with with GNP executed on it.
 */
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
    if(the_user_params->canvas_color)
      the_canvas = init_canvas(canvas_dims, canvas_dims,
          the_user_params->canvas_color->r, the_user_params->canvas_color->g,
          the_user_params->canvas_color->b);
    else
      the_canvas = init_canvas(canvas_dims, canvas_dims, MIN_COL, MIN_COL,
          MIN_COL);
  } else
    the_canvas = init_canvas(canvas_dims, canvas_dims, MIN_COL, MIN_COL,
        MIN_COL);
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

/**
 * This function executed the GNM variation (if any user parameter is not
 * specified or NULL is sent to this function it will fallback on the defaults).
 * @param the_user_params - The user paramters that were specified.
 * @return     the_canvas - The canvas with with GNM executed on it.
 */
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
    if(the_user_params->canvas_color)
      the_canvas = init_canvas(canvas_dims, canvas_dims,
          the_user_params->canvas_color->r, the_user_params->canvas_color->g,
          the_user_params->canvas_color->b);
    else
      the_canvas = init_canvas(canvas_dims, canvas_dims, MIN_COL, MIN_COL,
          MIN_COL);
  } else
    the_canvas = init_canvas(canvas_dims, canvas_dims, MIN_COL, MIN_COL,
        MIN_COL);
  int tmp = the_g_struct->m;
  int * i_collection = calloc(the_g_struct->m, sizeof(int));
  int * j_collection = calloc(the_g_struct->m, sizeof(int));
  graph = make_circular_node_collection(the_canvas, the_g_struct->n,
      path_to_font, font_size, canvas_dims);
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

/**
 * This function arranges the nodes so it is ``human readible" (in a circle).
 * @param   the_canvas - The canvas that the nodes will be arranged on.
 * @param            n - The n parameter of the erdos_renyi variation.
 * @param path_to_font - The path to the font file.
 * @param    font_size - The size of the font.
 * @param  canvas_dims - The dimension of the height and width of the canvas.
 * @return       graph - The nodes properly arranged.
 */
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

/**
 * This function determines if value is in collection from 0 to index.
 * @param collection - The collection of integers to check.
 * @param      value - The value to check for.
 * @param      index - The index to check up to.
 * @return         1 - Found.
 *                -1 - Not Found.
 */
int not_in_collection(int * collection, int value, int index) {
  for(int i = 0; i < index; i++)
    if(collection[i] == value)
      return -1;
  return 1;
}

/**
 * This function makes a node name from an integer.
 * @param     i - The int to be appended to NAME_CHAR.
 * @return name - The NAME_CHAR with i appended to it.
 */
char * make_node_name(int i) {
  int name_len = snprintf(NULL, 0, "%d", i) + 1;
  char * name = calloc(name_len + 1, sizeof(char));
  name[0] = NAME_CHAR;
  snprintf(name + 1, name_len, "%d", i);
  return name;
}

/**
 * Returns an integer from 0-99.
 * @param N/a
 * @return .\ - An int from 0-99.
 */
int random_number(void) {
  return rand() % 100;
}
