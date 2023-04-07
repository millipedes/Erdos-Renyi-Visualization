#include "../probability/include/erdos_renyi.h"
#include "../canvas/include/canvas.h"
#include <time.h>

int main(int argc, char ** argv) {
  srand(time(NULL));
  if(argc <= 1) {
    fprintf(stdout, "[MAIN]: Note, no config file given, running with defaults"
        "\n");
    canvas the_canvas = Gnm(NULL);
    write_canvas(the_canvas, DEFAULT_OUT_FILE);
    free_canvas(the_canvas);
  }
  for(int i = 1; i < argc; i++) {
    user_params the_user_params = init_user_params(argv[i]);
    canvas the_canvas = NULL;
    if(!the_user_params->the_g_struct)
      the_canvas = Gnm(NULL);
    else if(the_user_params->the_g_struct->m_or_p == 'p')
      the_canvas = Gnp(the_user_params);
    else
      the_canvas = Gnm(the_user_params);
    write_canvas(the_canvas, the_user_params->out_file);
    free_canvas(the_canvas);
    free_user_params(the_user_params);
  }
  return 0;
}
