#include "include/erdos_renyi.h"

canvas G(int n, double p) {
  int central_radius = (int)((double)CANVAS_DIMS / 3.0);
  int central_xy = CANVAS_DIMS / 2;
  double angle_between_node = 2 * M_PI / (double) n;
  int * x_coords = calloc(n, sizeof(int));
  int * y_coords = calloc(n, sizeof(int));
  for(int i = 0; i < n; i++) {
    x_coords[i] = central_xy + central_radius * cos(angle_between_node * i);
    y_coords[i] = central_xy + central_radius * sin(angle_between_node * i);
  }
  canvas the_canvas = init_canvas(CANVAS_DIMS, CANVAS_DIMS);
  node * graph = calloc(n, sizeof(struct NODE_T *));

  for(int i = 0; i < n; i++) {
    graph[i] = init_node("t1", init_pixel(0, 190, 255), x_coords[i], y_coords[i], 60);
    write_node(the_canvas, graph[i]);
  }
  
  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
      if(i != j)
        if(random_number() <= p * 100)
          connect_node(the_canvas, graph[i], graph[j]);

  for(int i = 0; i < n; i++)
    free_node(graph[i]);

  return the_canvas;
}

int random_number(void) {
  return rand() % 100;
}
