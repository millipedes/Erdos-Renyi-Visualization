#include "../probability/include/erdos_renyi.h"
#include "../file_io/include/file_io.h"
#include <time.h>

int main(void) {
  srand(time(NULL));
  user_params the_user_params = init_user_params("example_config/config");
  debug_user_params(the_user_params);
  free_user_params(the_user_params);
  // canvas the_canvas_one = Gnp(30, 1.0);
  // canvas the_canvas = Gnm(15, 10);
  // write_canvas(the_canvas, "test1.ppm");
  // write_canvas(the_canvas_one, "test2.ppm");
  // free_canvas(the_canvas);
  // free_canvas(the_canvas_one);
  return 0;
}
