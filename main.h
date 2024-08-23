#ifndef MAIN_H_
#define MAIN_H_
#include <curses.h>
#include "canvas.h"

/*
 * creates the background window and canvas window,
 * returns false if any window failed to create
 * returns true if both were created correctly
*/
bool create_windows(struct square_map *canvas, WINDOW** content, WINDOW** background, int *starty, int *startx);

/*
 * creates background window for the playing canvas,
 * returns a pointer to it
*/
WINDOW *create_background(struct square_map *canvas, int *start_y, int *start_x);

/*
 * creates a window representing the canvas, inside the background window
 * returns a pointer to it
*/
WINDOW *wcreate_canvas(struct square_map *canvas, int *start_y, int *start_x);


#endif // MAIN_H_
