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

  fill_top_bottom(map, side_length, TOP);

  /*print the side_length-2 inside lines of the square*/
  for(int j = 1; j < side_length-1; j++){
    for(int i = 0; i <side_length; i++){
        if(i == 0 ){ map->key[j][i] = '@';  } // left border
        else if(i == side_length-1){ map->key[j][i] = '@'; } // right border
        else { map->key[j][i] = ' '; }
    }
  }

  fill_top_bottom(map, side_length, BOT);
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

void print_canvas(struct square_map* map){
    for(int j = 0; j < map->side_length; j++){
      for(int i = 0; i < map->side_length; i++){
        printf("%c", map->key[i][j]);
    }
      printf("\n");
  }
}

void fill_top_bottom(struct square_map* map, int side_length,int type){
  if(type == TOP){
    for(int i = 0; i < side_length; i++){
    map->key[0][i] = '@';
    }
  }
  else if(type == BOT){
    for(int i = 0; i < side_length; i++){
    map->key[side_length-1][i] = '@';
    }
  }
}

/*
 * spawns fruit randomly within the canvas
 * if the fruit is spawned waits,
*/
bool spawn_fruit(struct square_map* map, int side_length, bool is_spawned){
  srand(time(NULL));
  const int border_thickness = 1;
  const int inside_width_height = side_length - 2*border_thickness;
  int fruit_y = 1 + rand() % (inside_width_height-1),
      fruit_x = 1 + rand() % (inside_width_height-1);
  map->key[fruit_y][fruit_x] = '*';
}
