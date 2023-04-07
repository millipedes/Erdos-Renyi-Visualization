#include "../../tests/include/connections.h"
#include "../probability/include/erdos_renyi.h"
#include <time.h>

int main(void) {
  srand(time(NULL));
  canvas the_canvas = G(15, 0.45);
  write_canvas(the_canvas, "test.ppm");
  free_canvas(the_canvas);
  // connection_test();
  return 0;
}
