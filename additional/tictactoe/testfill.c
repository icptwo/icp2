#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define NUMSIDE 3
#define NUMCELLS (NUMSIDE * NUMSIDE)
void Cells_print(int * cells, bool twod)
{
  if (twod == false)
    {
      int ind;
      for (ind = 0; ind < NUMCELLS; ind ++)
	{ printf("%c ", cells[ind]); }
      printf("\n\n");
      return;
    }
  int indr;
  int indc;
  for (indr = 0; indr < NUMSIDE; indr ++)
    {
      for (indc = 0; indc < NUMSIDE; indc ++)
	{
	  { printf("%c ", cells[indr * NUMSIDE + indc]); }
	}
      printf("\n");
    }
  printf("\n");
}

bool Cells_fill(int * cells, int numX, int numO, int ind)
// how many more X or O need to fill?
// the largest index already used for X or O?
{
  if ((numX == 0) && (numO == 0))
    {
      Cells_print(cells, false);
      return true;
    } // successful
  if (numX > (NUMCELLS - ind))
    { return false; } // do not have enough cells to fill X
  if (numO > (NUMCELLS - ind))
    { return false; } // do not have enough cells to fill O
  // fill X
  if (numX > 0)
    {
      cells[ind] = 'X';
      Cells_fill(cells, numX - 1, numO, ind + 1);
      cells[ind] = '-'; // unfill the cell
    }
  // fill O
  if (numO > 0)
    {
      cells[ind] = 'O';
      Cells_fill(cells, numX, numO - 1, ind + 1);
      cells[ind] = '-'; // unfill the cell
    }  
  Cells_fill(cells, numX, numO, ind + 1);
  return false;
}

void Board_fill(int numfill)
{
  int cells[NUMCELLS];
  int ind;
  for (ind = 0; ind < NUMCELLS; ind ++)
    { cells[ind] = '-'; }
  int numO = numfill / 2;
  int numX = numfill - numO;
  Cells_fill(cells, numX, numO, 0);
}

int main(int argc, char * * argv)
{
  // if (argc < 2) { return EXIT_FAILURE; }
  int numfill;
  // numfill = strtol(argv[1], NULL, 10);
  for (numfill = 1; numfill <= NUMCELLS; numfill ++)
    {
      Board_fill(numfill);
    }
  for (numfill = 1; numfill < NUMCELLS; numfill ++)
    {
      
    }
  return EXIT_SUCCESS;
}
