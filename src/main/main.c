/**
 * @file   main.c
 * @brief  This file contains the entry point to the code. It checks for cammand
 * line params and loads those configs, otherwise just executes on default
 * settings.
 * @author Matthew C. Lindeman
 * @date   Arpil 07, 2023
 * @bug    None known
 * @todo   Nothing
 */
#include "../probability/include/erdos_renyi.h"
#include <time.h>

int main(int argc, char ** argv) {
  srand(time(NULL));
  if(argc <= 1) {
    fprintf(stdout, "[MAIN]: Note, no config file given, running with defaults"
        "\n");
    canvas the_canvas = Gnm(NULL);
    write_canvas(the_canvas, DEFAULT_OUT_FILE);
    free_canvas(the_canvas);
  } else {
    for(int i = 1; i < argc; i++) {
      if(argv[i][0] == '-')
        i++;
      else {
        path_wrapper the_path_wrapper = init_path_wrapper(argv[i]);
        user_params the_user_params = init_user_params(the_path_wrapper->path_file);
        canvas the_canvas = NULL;
        if(!the_user_params->the_g_struct)
          the_canvas = Gnm(NULL);
        else if(the_user_params->the_g_struct->m_or_p == 'p')
          the_canvas = Gnp(the_user_params);
        else
          the_canvas = Gnm(the_user_params);
        if(the_user_params->out_file->type == PNG
            || the_user_params->out_file->type == NONE)
          write_canvas_png(the_canvas, the_user_params->out_file->path_file);
        else
          write_canvas(the_canvas, the_user_params->out_file->path_file);
        free_path_wrapper(the_path_wrapper);
        free_canvas(the_canvas);
        free_user_params(the_user_params);
      }
    }
  }
  return 0;
}
