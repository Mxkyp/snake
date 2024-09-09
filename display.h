#include <stdbool.h>
#include <curses.h>
#include "point.h"

struct GameBoard{
  WINDOW *content_square;
  WINDOW *background_square;
  struct point background_upper_left_corner;
  int content_win_side_length;
};
/*
 * creates the background window and canvas window,
 * returns false if any window failed to create
 * returns true if both were created correctly
*/
struct GameBoard* create_game_board(const int side_length);

/*
 free's the GameBoard
 */
void delete_game_board(struct GameBoard* board);
/*
 * creates background window for the playing canvas,
 * returns a pointer to it
*/
WINDOW *create_background(int side_length, struct point *background_upper_left_corner);

/*
 * creates a window for the content (where the game will take place) , inside the background window
 * returns a pointer to it
*/
WINDOW *create_content(int side_length, struct point *background_upper_left_corner);


void end_screen(struct GameBoard *board, int score);

void print_score(int game_score, struct point *background_upper_left_corner);
