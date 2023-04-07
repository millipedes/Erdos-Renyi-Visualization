#ifndef ERD_H
#define ERD_H

#include "../../canvas/include/canvas.h"

#define CANVAS_DIMS 1000
#define NAME_CHAR 'n'

canvas Gnp(int n, double p);
canvas Gnm(int n, int m);
node * make_circular_node_collection(canvas the_canvas, int n);
char * make_node_name(int i);
int not_in_collection(int * collection, int value, int index);
int random_number(void);

#endif
