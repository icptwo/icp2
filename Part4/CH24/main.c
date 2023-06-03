// CH24: main.c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "maze.h"
int main(int argc, char * * argv)
{
  // argv[1]: input
  // output uses printf
  if (argc < 2)  { return EXIT_FAILURE; }
  Maze * maz;
  bool rtv;
  rtv = readMaze(argv[1], & maz);
  if (rtv == false)  { return EXIT_FAILURE;  }
  findDistance(maz);
  printMaze(maz);
  freeMaze(maz);
  return EXIT_SUCCESS;
}
