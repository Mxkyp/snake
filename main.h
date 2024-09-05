#ifndef MAIN_H_
#define MAIN_H_
#include <curses.h>
#include "canvas.h"
#include <stdbool.h>
#include <time.h>

/*
 * creates the background window and canvas window,
 * returns false if any window failed to create
 * returns true if both were created correctly
*/
bool create_windows(int side_length, WINDOW** content, WINDOW** background, int *starty, int *startx);

/*
 * creates background window for the playing canvas,
 * returns a pointer to it
*/
WINDOW *create_background(int side_length, int *start_y, int *start_x);

/*
 * creates a window representing the canvas, inside the background window
 * returns a pointer to it
*/
WINDOW *wcreate_canvas(int side_length, int *start_y, int *start_x);

/*
  if not spawned or spawned at least FRUIT_LIFETIME_SECONDS away,
  delets old fruit, creates new, prints it and restarts the fruit timer
 */
void manage_fruit(WINDOW *content, struct fruit *fr);

/*
 gives a 300ms window for inputing a char
 */
void get_move(int *c);

#endif // MAIN_H_
