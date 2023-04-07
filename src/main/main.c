#include "../../tests/include/connections.h"
#include "../probability/include/erdos_renyi.h"
#include <time.h>

int main(void) {
  srand(time(NULL));
  // canvas the_canvas = Gnp(15, 0.15);
  canvas the_canvas = Gnm(15, 10);
  write_canvas(the_canvas, "test.ppm");
  free_canvas(the_canvas);
  // connection_test();
  return 0;
}
