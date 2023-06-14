// CH24:maze.c
#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
// directions, ORIGIN marks the starting point 
enum {ORIGIN, EAST, SOUTH, WEST, NORTH};
// move forward or backward
enum {FORWARD, BACKWARD};
bool readMaze(const char * filename, Maze ** maz)
{
  FILE * fptr = fopen(filename, "r");
  if (fptr == NULL)
    { return false; }
    int linelen = 0;
  int maxlinelen = 0;
  int numline = 0;
  int onech;
  while (! feof(fptr))
    {
      onech = fgetc(fptr);
      if (onech != EOF)
	{
	  if (onech == '\n') // end of a line
	    {
	      numline ++;
	      if (maxlinelen < linelen)
		{ maxlinelen = linelen; }
	      linelen = 0;
	    }
       else
	 { linelen ++; }
	}
    }
  if (numline <= 2) // invalid maze
    {
      fclose (fptr);
      return false;
    }
  Maze * mz = malloc(sizeof(Maze));
  * maz = mz;
  mz -> numrow = numline;
  mz -> numcol = maxlinelen;
  mz -> cells = malloc(sizeof(int *) * numline);
  int indrow = 0;
  int indcol = 0;
  for (indrow = 0; indrow < numline; indrow ++)
    {
      (mz -> cells)[indrow] = malloc(sizeof(int) * maxlinelen);
      // assume this malloc succeeds, do not check
      for (indcol = 0; indcol < maxlinelen; indcol ++)
	{
	  // set every cell to -1 (not reachable)
	  (mz -> cells)[indrow][indcol] = -1;
	}
    }
  // return to the beginning of the file
  fseek(fptr, 0, SEEK_SET);
  indrow = 0;
  indcol = 0;
  int maxlength = 2 * numline * maxlinelen + 1; 
  while (indrow < numline)
    {
      bool breakline = false;
      while (breakline == false)
	{
	  onech = fgetc(fptr);
	  if (onech == EOF)
	    { return false; } // should not happen
	  switch (onech)
	    {
	    case ' ': // corridor
	    case 'E': // exit
	      // possibly reachable
	      // make the value large enough and they must be reduced
	      // if the value does not reduce, it is not reachable
	      mz -> cells[indrow][indcol] = maxlength;
	      break;
	    case 's': // starting point
	      mz -> cells[indrow][indcol] = 0; // distance is 0
	      mz -> startrow = indrow;
	      mz -> startcol = indcol;
	      break;
	    case '\n':
	      breakline = true;
	      break;
	    case 'b': // brick
	      mz -> cells[indrow][indcol] = -1; // unreachable
	    }
	  indcol ++;
	}
      indrow ++;
      indcol = 0;
    }
  fclose (fptr);
  return true;
}
void printMaze(Maze * maz)
{
  if (maz == NULL)
    {
      return;
    }
  int indrow;
  int indcol;
  for (indrow = 0; indrow < (maz -> numrow); indrow ++)
    {
        for (indcol = 0; indcol < (maz -> numcol); indcol ++)
	  { printf("%4d ", (maz -> cells)[indrow][indcol]); }
	printf("\n");
    }
}
void freeMaze(Maze * maz)
{
  int indrow;
  for (indrow = 0; indrow < (maz -> numrow); indrow ++)
    {
      free ((maz -> cells)[indrow]);
    }
  free (maz -> cells);
  free (maz);
}
static int nextDistance(Maze * maz, int row, int col, int dir)
{
  /* (row, col) is the current location */
  switch (dir)
    {
    case NORTH: row --; break;
    case SOUTH: row ++; break;
    case WEST:  col --; break;
    case EAST:  col ++; break;
    }
  // check invalid index, -1 means cannot enter the cell
  if (row < 0) { return -1; }
  if (row >= (maz -> numrow)) { return -1; }
  if (col < 0) { return -1; }
  if (col >= (maz -> numcol)) { return -1; }
  // valid index, check the cell
  return (maz->cells)[row][col];
}
static void move(Maze * maz, int row, int col, int distance)
{
  int dest; // the distance from this cell to the starting point
  if (distance == -1)
    {
      fprintf(stderr, "WRONG. Enter a brick.\n");
      return;
    }
  (maz -> cells)[row][col] = distance;
  // move if the a neighbor's distance is larger
  // than the current distance + 1
  dest = nextDistance(maz, row, col, EAST);
  if (dest > (distance + 1)) // move can shorten the distance
    { move(maz, row, col + 1, distance + 1); }
  dest = nextDistance(maz, row, col, WEST);
  if (dest > (distance + 1))
    { move(maz, row, col - 1, distance + 1); }
  dest = nextDistance(maz, row, col, NORTH);
  if (dest > (distance + 1))
    { move(maz, row - 1, col, distance + 1); }
  dest = nextDistance(maz, row, col, SOUTH);
  if (dest > (distance + 1))
    { move(maz, row + 1, col, distance + 1); }
}
void findDistance(Maze * maz)
{
  if (maz == NULL) { return; }
  move(maz, maz -> startrow, maz -> startcol, 0);
  // mark unreachable cells as -1
  int row, col;
  int maxlength = 2 * (maz -> numrow) * (maz -> numcol) + 1;
  for (row = 0; row < (maz -> numrow); row ++)
    {
      for (col = 0; col < (maz -> numcol); col ++)
	{
	  if ((maz -> cells[row][col]) == maxlength)
	    { maz -> cells[row][col] = -1; }
	}
    }
}
