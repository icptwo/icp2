#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char * * argv)
{
  // If argc is 1, all 6045 cases are printed
  // If argc is 2:
  //    argv[1] is "s": stop when the winner is known or definitely draw
  //    argv[1] is "e": eliminate rotation or mirror equivalent
  if (argc > 2) // should be only 1 or 2
    { return EXIT_FAILURE; }
  
  
  int choice = strtol(argv[1], NULL, 10);
  
  
  Graph * brgf;
  brgf = malloc(sizeof(Graph));
  Board * brhead = NULL;
  int numfill;
  for (numfill = 1; numfill <= NUMCELLS; numfill ++)
    {
      brhead = NULL;
      Board_add(numfill, & brhead);
      // printf("final results for %d:\n", numfill);
      // Board_print(brhead);
      // printf("==============\n");
      brgf -> tttboard[numfill] = brhead;
    }
  /*
  printf("***********************\n");
  for (numfill = 1; numfill <= NUMCELLS; numfill ++)
    {
      brhead = brgf -> tttboard[numfill];
      printf("boards with %d filled cells:\n", numfill);
      Board_print(brhead);
    }
  */
  Graph_addEdge(brgf);
  for (numfill = 1; numfill <= NUMCELLS; numfill ++)
    {
      printf("numfill = %d\n", numfill);
      brhead = brgf -> tttboard[numfill];
      Board * br = brhead;
      GraphLink * gflk = NULL;
      while (br != NULL)
	{
	  printf("cells:\n");
	  Cells_print(br -> cells, true);
	  printf("parent:\n");
	  gflk = br -> parent;
	  while (gflk != NULL)
	    {
	      Cells_print(gflk -> brd -> cells, true);
	      gflk = gflk -> next;
	    }
	  printf("child:\n");
	  gflk = br -> child;
	  while (gflk != NULL)
	    {
	      Cells_print(gflk -> brd -> cells, true);
	      gflk = gflk -> next;
	    }
	  br = br -> next;
	}
    }
  return EXIT_SUCCESS;
}
