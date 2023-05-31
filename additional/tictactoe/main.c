#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tictactoe.h"
int main(int argc, char * * argv)
{
  int numfill;
  for (numfill = 1; numfill <= NUMCELL; numfill ++)
    {
      int numboard = generateBoard(numfill);
      printf("%d boards with %d filled cells\n",
	     numboard, numfill);
    }
  return EXIT_SUCCESS;
}
