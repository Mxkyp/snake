#include "../canvas.h"
#include "../worm.h"
#include <assert.h>
#include <time.h>
#include <stdbool.h>
#include <curses.h>
#define EXPECTED_ARGC 2
bool validate_argc(int argc, int expected_argc);

int main(int argc, char *argv[]){
  assert(validate_argc(argc,EXPECTED_ARGC));
  const WINDOW *content = (const WINDOW *) argv[2];


}

bool validate_argc(int argc, int expected_argc){
  if(argc == expected_argc){
    return true;
  }
  return false;
}
