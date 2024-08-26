#ifndef WORM_H_
#define WORM_H_
#include "canvas.h"
#include <stdlib.h>
#include <curses.h>



struct snake{
  struct point coords;
  struct snake *next;
  struct snake *before;
};



struct snake *create_snake(const int canvas_side_length);



void print_snake(WINDOW * win, struct snake *s, struct point old_tail_coords);



void update_snake(WINDOW *win, struct snake **s, const int direction);

#endif
