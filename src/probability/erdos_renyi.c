#include "include/erdos_renyi.h"

// canvas G(int n, double p) {
//   int sqrt_n = (int)sqrt(n);
//   printf("%d\n", sqrt_n);
//   canvas the_canvas = init_canvas(sqrt_n, sqrt_n);
//   node * graph = calloc(n, sizeof(struct NODE_T *));
//   for(int i = 0; i < sqrt_n; i++)
//     for(int j = 0; j < sqrt_n; j++)
//       graph[i * j + j] = init_node("t1", init_pixel(0, 190, 255), i/2*sqrt_n, j/2*sqrt_n, sqrt_n/2);
//   for(int i = 0; i < n; i++)
//     if(graph[i])
//       write_node(the_canvas, graph[i]);
//   write_canvas(the_canvas, "test.ppm");
//   return NULL;
// } 
