#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <curses.h>
#include <time.h>
#include "../main.h"
#include "../display.h"
#include "../game_elements.h"
#include "../point.h"
#define SIDE_LENGTH 15

int main(void){
  initscr();

  //background and content display
  struct GameBoard *board = create_game_board(SIDE_LENGTH);
  assert(board);
  set_curses_input_options();

  //snake and fruit
  struct GameElements* game = create_game_elements();
  assert(game);

  while(true){
    render(board, game);
    input(&game->snake_head->move_direction);
    if(move_snake(board->content_win_side_length, game) == false){
      end_screen(board, game->snake_head->game_score);
      break;
    }
    wclear(board->content_square);
  }

  clear();
  endwin();
  delete_game_elements(board, game);
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

void delete_game_elements(struct GameBoard* board, struct GameElements *game){
  delete_snake(game->snake_head);
  free(game->fruit);
  delete_game_board(board);
}

void set_curses_input_options(){
  cbreak();
  noecho();
}

void render(struct GameBoard *board, struct GameElements *game_elements){
    manage_fruit(board->content_square, game_elements);
    print_fruit(board->content_square, &game_elements->fruit->coords);
    print_snake(board->content_square, game_elements->snake_head);
    print_score(game_elements->snake_head->game_score, &board->background_upper_left_corner);
    wrefresh(board->content_square);
}

void input(int *direction){
    static int c;
    get_move(&c);
    set_and_validate_direction(direction, c);
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
    timeout(400);
    *c = getch();
    usleep(4000);
    flushinp();
}

void set_and_validate_direction(int *direction, int input_ch){
    int last_direction = *direction;

    switch(input_ch){
      case 'w': *direction = UP;
        break;
      case 'd': *direction = RIGHT;
        break;
      case 's': *direction = DOWN;
        break;
      case 'a': *direction = LEFT;
        break;
    };

    if(last_direction == *direction + 1 || last_direction == *direction - 1){
      *direction = last_direction;
    } // prevent the snake from doing 180 degree turns
}

void print_score(int game_score, struct point *background_upper_left_corner){
  mvprintw(background_upper_left_corner->y - 1, background_upper_left_corner->x + 1, "score:%d", game_score);
}
