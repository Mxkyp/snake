#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <curses.h>
#include <time.h>
#include "../main.h"
#include "../fruit.h"
#include "../snake.h"
#include "../display.h"
#include "../point.h"
#define SIDE_LENGTH 25

int main(void){
  initscr();

  //background and content display
  WINDOW *content = NULL, *background = NULL;
  struct point background_upper_left_corner;
  assert(create_windows(SIDE_LENGTH, &content, &background, &background_upper_left_corner));
  cbreak();
  noecho();

  //snake and fruit
  struct GameElements* game_elements = create_game_elements();

  while(true){
    render(content, game_elements, &background_upper_left_corner);
    input(&game_elements->snake_head->move_direction);
    if(move_snake(SIDE_LENGTH, game_elements->snake_head, game_elements->fruit) == false){ end_screen(content, game_elements->snake_head->game_score, SIDE_LENGTH); break; }
    wclear(content);
  }

  clear();
  endwin();
  return 0;
}

struct GameElements* create_game_elements(){
  struct GameElements* new = malloc(sizeof(*new));
  assert(new);

  new->snake_head = create_snake(SIDE_LENGTH);
  assert(new->snake_head);

  new->fruit = create_fruit();
  assert(new->fruit);

  return new;
}

void render(WINDOW *content,struct GameElements *game_elements,struct point *background_upper_left_corner){
    manage_fruit(content, game_elements);
    print_fruit(content, &game_elements->fruit->coords);
    print_snake(content, game_elements->snake_head);
    print_score(game_elements->snake_head->game_score, background_upper_left_corner);
    wrefresh(content);
}

void input(int *direction){
    static int c;
    int last_direction = *direction;
    get_move(&c);

    switch(c){
      case 'w': *direction = UP;
        break;
      case 'd': *direction = RIGHT;
        break;
      case 's': *direction = DOWN;
        break;
      case 'a': *direction = LEFT;
        break;
    }
    if(last_direction == *direction + 1 || last_direction == *direction - 1){ // prevent the snake from doing 180 degree turns
                                                                              // this works because directions are enum's
                                                                              // UP = 0 DOWN = 1, LEFT = 3 RIGHT = 4
      *direction = last_direction;
    }
}

void manage_fruit(WINDOW *content, struct GameElements *game_elements){
    if(check_fruit(game_elements->fruit)){
      mvwdelch(content, game_elements->fruit->coords.y, game_elements->fruit->coords.x);
      spawn_fruit(content, game_elements, SIDE_LENGTH);
      time(&game_elements->fruit->spawn_time);
      game_elements->fruit->is_spawned = true;
    }
}

void get_move(int *c){
    timeout(300);
    *c = getch();
    flushinp();
}

void print_score(int game_score, struct point *background_upper_left_corner){
  mvprintw(background_upper_left_corner->y - 1, background_upper_left_corner->x + 1, "score:%d", game_score);
}
