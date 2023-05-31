#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tictactoe.h"
#define NUMDIM 1
static void printCells(int * cells, int dim)
{
  if (dim == 1)
    {
      int ind;
      for (ind = 0; ind < NUMCELL; ind ++)
	{ printf("%c", cells[ind]); }
      printf("\n");
      return;
    }
  if (dim == 2)
    {
      int ind = 0;
      int row;
      int col;
      for (row = 0; row < NUMSIDE; row ++)
	{
	  for (col = 0; col < NUMSIDE; col ++)
	    {
	      printf("%c", cells[ind]);
	      ind ++;
	    }
	  printf("\n");
	}
      printf("\n");
      return;
    }
}
static void fillCells(int * cells, int numX, int numO,
		      int * numboard, int ind);
int generateBoard(int numfill)
{
  int numboard = 0;
  int numO = numfill / 2;
  int numX = numfill - numO;
  int cells[NUMCELL];
  int ind;
  for (ind = 0; ind < NUMCELL; ind ++)
    { cells[ind] = '.'; }
  fillCells(cells, numX, numO,& numboard, 0);
  return numboard;
}
static void fillCells(int * cells, int numX, int numO,
		      int * numboard, int ind)
{
  if ((numX == 0) && (numO == 0)) // succeed
    {
      printCells(cells, NUMDIM);
      (* numboard) ++;
      return;
    }
  if (numX > (NUMCELL - ind)) // fail, don't have enough cells left
    {
      return;
    }
  if (numO > (NUMCELL - ind)) // fail
    {
      return;
    }
  if (numX > 0)
    {
      cells[ind] = 'X';
      fillCells(cells, numX - 1, numO, numboard, ind + 1);
      cells[ind] = '.'; // unfill the cell
    }
  if (numO > 0)
    {
      cells[ind] = 'O';
      fillCells(cells, numX, numO - 1, numboard, ind + 1);
      cells[ind] = '.'; // unfill the cell
    }
  // keep this cell as unfilled
  fillCells(cells, numX, numO, numboard, ind + 1);
}
