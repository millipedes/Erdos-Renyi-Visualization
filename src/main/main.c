#include "../probability/include/erdos_renyi.h"
#include "../canvas/include/canvas.h"
#include <time.h>

int main(void) {
  srand(time(NULL));
  user_params the_user_params = init_user_params("example_config/config");
  canvas the_canvas = Gnm(NULL);
  write_canvas(the_canvas, the_user_params->out_file);
  free_canvas(the_canvas);
  free_user_params(the_user_params);
  return 0;
}
