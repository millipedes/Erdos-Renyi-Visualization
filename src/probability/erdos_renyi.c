#include "include/erdos_renyi.h"

canvas Gnp(int n, double p) {
  canvas the_canvas = init_canvas(CANVAS_DIMS, CANVAS_DIMS);
  node * graph = make_circular_node_collection(the_canvas, n);
  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
      if(i != j)
        if(random_number() <= p * 100)
          connect_node(the_canvas, graph[i], graph[j]);
  for(int i = 0; i < n; i++)
    free_node(graph[i]);
  return the_canvas;
}

canvas Gnm(int n, int m) {
  int tmp = m;
  int * i_collection = calloc(m, sizeof(int));
  int * j_collection = calloc(m, sizeof(int));
  int current_collection_index = 0;
  int i_rand = 0;
  int j_rand = 0;
  canvas the_canvas = init_canvas(CANVAS_DIMS, CANVAS_DIMS);
  node * graph = make_circular_node_collection(the_canvas, n);
  while(tmp > 0) {
    i_rand = rand() % n;
    j_rand = rand() % n;
    if(i_rand != j_rand
        && not_in_collection(i_collection, i_rand, current_collection_index) != -1
        && not_in_collection(j_collection, j_rand, current_collection_index) != -1) {
      i_collection[current_collection_index] = i_rand;
      j_collection[current_collection_index] = j_rand;
      current_collection_index++;
      tmp--;
    }
  }
  for(int i = 0; i < m; i++)
    connect_node(the_canvas, graph[i_collection[i]], graph[j_collection[i]]);
  return the_canvas;
}

node * make_circular_node_collection(canvas the_canvas, int n) {
  int central_radius = (int)((double)CANVAS_DIMS / 3.0);
  int central_xy = CANVAS_DIMS / 2;
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
    write_node(the_canvas, graph[i]);
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
