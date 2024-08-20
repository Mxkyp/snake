#include "main.h"
#include "canvas.h"
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <curses.h>
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))
#define clear_1() printf("\033[H\033[J")

int main(void){
  struct square_map *canvas = create_canvas(20);

    clear_1();
    gotoxy(0,0);
  while(true){
    spawn_fruit(canvas, 20, false);
    clear();
    fflush(stdout);
    gotoxy(0,0);
    print_canvas(canvas);
    sleep(1);
  }
  return 0;
}
