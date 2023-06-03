// CH24:maze.h
#ifndef MAZE_H
#define MAZE_H
#include <stdbool.h>
typedef struct
{
  int * * cells;
  int numrow;
  int numcol;
  int startrow;
  int startcol;
} Maze;
bool readMaze(const char * filename, Maze * * maz);
void printMaze(Maze * maz);
void freeMaze(Maze * maz); 
void findDistance(Maze * maz); // shortest distance of each reachable ell
#endif
