#include "main.h"
#include "canvas.h"
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(void){
  struct square_map *map = create_canvas(20);
  if(map == NULL){ printf("FAILURE!"); }
  for(int i=0;i<20;i++){
    for(int j=0; j<20; j++){
      printf("%c",map->key[i][j]);
    }
    printf("\n");
  }
  return 0;
}
