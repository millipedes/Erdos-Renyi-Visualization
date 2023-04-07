#include "include/move.h"

move init_move(char * white, char * black, int no) {
  move the_move = calloc(1, sizeof(struct MOVE_T));
  size_t white_len = strnlen(white, MAX_MOVE_SIZE);
  size_t black_len = strnlen(black, MAX_MOVE_SIZE);
  the_move->white = calloc(white_len + 1, sizeof(char));
  strncpy(the_move->white, white, white_len);
  the_move->black = calloc(black_len + 1, sizeof(char));
  strncpy(the_move->black, black, black_len);
  the_move->no = no;
  return the_move;
}

void debug_move(move the_move) {
  printf("%d: `%s` `%s`\n", the_move->no, the_move->white, the_move->black);
}

void free_move(move the_move) {
  if(the_move) {
    if(the_move->white)
      free(the_move->white);
    if(the_move->black)
      free(the_move->black);
    free(the_move);
  }
}
