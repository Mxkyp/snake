#include <stdbool.h>
#include <curses.h>

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
 * creates a window for the content (where the game will take place) , inside the background window
 * returns a pointer to it
*/
WINDOW *create_content(int side_length, int *start_y, int *start_x);


void end_screen(WINDOW *main, int score, int side_length);

void print_score(int game_score, int starty, int startx);
