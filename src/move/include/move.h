#ifndef MOVE_H
#define MOVE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MOVE_SIZE 64

typedef struct MOVE_T {
  char * white;
  char * black;
  int no;
} * move;

move init_move(char * white, char * black, int no);
void debug_move(move the_move);
void free_move(move the_move);

#endif
