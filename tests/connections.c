/**
 * NOTE
 * This file was made long ago in the infrastructure of the program and at the
 * moment I don't really feel like fixing it lol. Open to PRs tho.
 */

#include "include/connections.h"

// void connection_test(void) {
//   canvas the_canvas = init_canvas(1000, 1000);
//   char * t1 = calloc(3, sizeof(char));
//   t1[0] = 't';
//   t1[1] = '1';
//   node the_node = init_node(t1, init_pixel(0, 190, 255), 500, 500, 100);
//   char * t2 = calloc(3, sizeof(char));
//   t2[0] = 't';
//   t2[1] = '2';
//   node the_node1 = init_node(t2, init_pixel(0, 190, 255), 250, 500, 100);
//   char * t3 = calloc(3, sizeof(char));
//   t3[0] = 't';
//   t3[1] = '3';
//   node the_node2 = init_node(t3, init_pixel(0, 190, 255), 500, 250, 100);
//   char * t4 = calloc(3, sizeof(char));
//   t4[0] = 't';
//   t4[1] = '4';
//   node the_node3 = init_node(t4, init_pixel(0, 190, 255), 500, 750, 100);
//   char * t5 = calloc(3, sizeof(char));
//   t5[0] = 't';
//   t5[1] = '5';
//   node the_node4 = init_node(t5, init_pixel(0, 190, 255), 250, 250, 100);
//   char * t6 = calloc(3, sizeof(char));
//   t6[0] = 't';
//   t6[1] = '6';
//   node the_node5 = init_node(t6, init_pixel(0, 190, 255), 750, 250, 100);
//   char * t7 = calloc(3, sizeof(char));
//   t7[0] = 't';
//   t7[1] = '7';
//   node the_node6 = init_node(t7, init_pixel(0, 190, 255), 750, 500, 100);
//   char * t8 = calloc(3, sizeof(char));
//   t8[0] = 't';
//   t8[1] = '8';
//   node the_node7 = init_node(t8, init_pixel(0, 190, 255), 250, 750, 100);
//   char * t9 = calloc(3, sizeof(char));
//   t9[0] = 't';
//   t9[1] = '9';
//   node the_node8 = init_node(t9, init_pixel(0, 190, 255), 750, 750, 100);
//   // debug_canvas(the_canvas);
//   the_canvas = write_node(the_canvas, the_node);
//   the_canvas = write_node(the_canvas, the_node1);
//   the_canvas = write_node(the_canvas, the_node2);
//   the_canvas = write_node(the_canvas, the_node3);
//   the_canvas = write_node(the_canvas, the_node4);
//   the_canvas = write_node(the_canvas, the_node5);
//   the_canvas = write_node(the_canvas, the_node6);
//   the_canvas = write_node(the_canvas, the_node7);
//   the_canvas = write_node(the_canvas, the_node8);
//   the_canvas = connect_node(the_canvas, the_node, the_node1);
//   the_canvas = connect_node(the_canvas, the_node, the_node2);
//   the_canvas = connect_node(the_canvas, the_node, the_node3);
//   the_canvas = connect_node(the_canvas, the_node, the_node4);
//   the_canvas = connect_node(the_canvas, the_node, the_node5);
//   the_canvas = connect_node(the_canvas, the_node, the_node6);
//   the_canvas = connect_node(the_canvas, the_node, the_node7);
//   the_canvas = connect_node(the_canvas, the_node, the_node8);
//   write_canvas(the_canvas, "test.ppm");
//   free_canvas(the_canvas);
//   free_node(the_node);
//   free_node(the_node1);
//   free_node(the_node2);
//   free_node(the_node3);
//   free_node(the_node4);
//   free_node(the_node5);
//   free_node(the_node6);
//   free_node(the_node7);
//   free_node(the_node8);
// }
