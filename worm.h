#ifndef WORM_H_
#define WORM_H_
#include "canvas.h"

struct snake{
  struct point *head, *tail;
  struct point body[];
};

/*
  allocates memory for a snake covering the whole canvas,
  if allocation is failed returns null
  assigns the starting y, x coordinates to its head
  assigns the tail pointer to its head
*/
struct snake* create_snake(int side_length);


/*
 * checks if a move in a given direction is doable, by calling check_move()
 * if yes return true, and move the snake by calling update_snake()
 * else return false
*/
bool move_snake(WINDOW *win, struct snake *s, const int side_length, struct point *fruit_position, const int direction);


bool check_move(struct snake *s,const int side_length, const int move_direction);


void update_snake(WINDOW* win, struct snake *s, const int direction);

/*
 * print the snake;
*/
bool print_snake(WINDOW *win, struct snake *s);

#endif // WORM_H_
