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
    return false;
  }

  struct square_map *map = malloc( sizeof(int) + side_length * sizeof(char*));

  for(int i = 0; i<side_length; i++){
    map->key[i] = malloc(side_length * sizeof(char));
    if(map->key[i] == NULL){
      return NULL;
    }
  }

  if(map == NULL){
    return NULL;
  }

  print_top_bottom(map, side_length, TOP);

  /*print the side_length-2 inside lines of the square*/
  for(int j = 1; j < side_length-1; j++){
    for(int i = 0; i <side_length; i++){
        if(i == 0 ){ map->key[j][i] = '@';  }
        else if(i == side_length-1){ map->key[j][i] = '@'; }
        else { map->key[j][i] = ' '; }
    }
  }

  print_top_bottom(map, side_length, BOT);
  return map;
}

void print_top_bottom(struct square_map* map, int side_length,int type){
  if(type == TOP){
    for(int i = 0; i < side_length; i++){
    map->key[0][i] = '@';
    }
  }
  else if(type = BOT){
    for(int i = 0; i < side_length; i++){
    map->key[side_length-1][i] = '@';
    }
  }
}

/*
 * spawns fruit randomly within the canvas
 * if the fruit is spawned waits,
*/
bool spawn_fruit(int side_length, bool is_spawned){
  srand(time(NULL));
  const int border_thickness = 1;
  const int inside_width_height = side_length - 2*border_thickness;
  int fruit_y = rand() % inside_width_height,
      fruit_x = rand() % inside_width_height;
  clear();
  gotoxy(0, 0);
}


void gotoxy(unsigned x, unsigned y)
{
  printf("\033[%d;%dH\033[2K", y, x);
}
