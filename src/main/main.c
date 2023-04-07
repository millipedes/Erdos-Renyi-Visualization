#include "../canvas/include/canvas.h"
#include "../canvas/include/node.h"

int main(void) {
  canvas the_canvas = init_canvas(1000, 1000);
  node the_node = init_node(init_move("e4567", "e5", 1), init_pixel(0, 190, 255), 300, 300, 150);
  node the_node1 = init_node(init_move("e45", "e5", 1), init_pixel(0, 190, 255), 500, 500, 75);
  node the_node2 = init_node(init_move("d45", "d5", 1), init_pixel(0, 190, 255), 300, 950, 100);
  // debug_canvas(the_canvas);
  the_canvas = write_node(the_canvas, the_node);
  the_canvas = write_node(the_canvas, the_node1);
  the_canvas = write_node(the_canvas, the_node2);
  the_canvas = connect_node(the_canvas, the_node, &the_node1, 1);
  the_canvas = connect_node(the_canvas, the_node, &the_node2, 1);
  write_canvas(the_canvas, "test.ppm");
  free_canvas(the_canvas);
  free_node(the_node);
  free_node(the_node1);
  free_node(the_node2);
  return 0;
}
