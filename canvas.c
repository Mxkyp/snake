#include "canvas.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <curses.h>
#define MIN_SIZE 8
#define TOP 0
#define BOT 1

struct square_map* create_canvas(int side_length){
  if(side_length < MIN_SIZE){
    printf("canvas too small");
    return NULL;
  }

  struct square_map* map = create_map(side_length);
  if(map == NULL){ return NULL; }
  map->side_length = side_length;

  for(int j = 1; j < side_length; j++){
    for(int i = 0; i <side_length; i++){
      map->key[i][j] = 'o';
    }
  }
  return map;
}

struct square_map* create_map(int side_length){
  struct square_map *map = malloc( sizeof(int) + side_length * sizeof(char*));

  for(int i = 0; i < side_length; i++){
    map->key[i] = malloc(side_length * sizeof(char));
    if(map->key[i] == NULL){
      return NULL;
    }
  }

  if(map == NULL){
    return NULL;
  }
  return map;
}

void print_canvas(WINDOW * win, struct square_map* map){
  if(win == NULL){
   win = stdscr;
  }
    for(int j = 0; j < map->side_length; j++){
      for(int i = 0; i < map->side_length; i++){
        wprintw(win, "%c", map->key[i][j]);
    }
  }
}
/*
 * spawns fruit randomly within the canvas
 * if the fruit is spawned waits,
*/
char *spawn_fruit(struct square_map* map, char*last_fruit, int side_length, bool is_spawned){
  static const char empty_cell = ' ';
  if(last_fruit != NULL){
    *last_fruit = empty_cell;
  }
  srand(time(NULL));
  int fruit_y =  rand() % side_length,
      fruit_x =  rand() % side_length;

  map->key[fruit_y][fruit_x] = '*';

  return &map->key[fruit_y][fruit_x];
}
