#ifndef CANVAS_H_
#define CANVAS_H_
#include <stdbool.h>
#include <curses.h>

struct square_map{
  int side_length;
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
 * if the fruit is spawned waits;
*/
char *spawn_fruit(struct square_map* map, char*last_fruit, int side_length, bool is_spawned);

/*
 * creates a map with side_length*side_length keys;
 * on failure, returns NULL;
*/
struct square_map* create_map(int side_length);


//minor functions

/*
  fills the top/bottom(they're the same) line of the canvas square;
*/
void fill_top_bottom(struct square_map* map, int side_length,int type);

void print_canvas(WINDOW * win, struct square_map* map);


#endif // CANVAS_H_
