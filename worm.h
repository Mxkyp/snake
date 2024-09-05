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


/*
 * creates a snake's head and returns it
 * doesnt check for proper creation
 * returns a pointer to it
*/
struct snake *create_snake(const int canvas_side_length);
/*
 ** creates a new node at the end of snake's body,
 ** checks if it was properly created with assert
 ** returns a pointer to it
*/
struct snake *new_node(struct snake *head);


void print_snake(WINDOW *win, struct snake *head);


bool move_snake(int direction, struct snake *head);

#endif
