#ifndef CANVAS_H_
#define CANVAS_H_
#include <stdbool.h>

struct square_map{
  int side_size;
  char *key[];
};
/*
 * creates a square canvas map,
 * fills it with the square representation
 * return the adress on success;
*/
struct square_map* create_canvas(int side_length);
/*
 * spawns fruit randomly within the canvas
 * if the fruit is spawned waits,
*/
bool spawn_fruit(int frequency_multiplier, bool is_spawned);


//minor functions

/*
  fills the top/bottom(they're the same) line of the canvas square;
*/
void print_top_bottom(struct square_map* map, int side_length,int type);
/*
 * goes to the x, y line
*/
void gotoxy(unsigned x, unsigned y);

#endif // CANVAS_H_
