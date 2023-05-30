#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tictactoe.h"
#define NUMBOARD 6045 // possible board configuration
// sum (n = 1 to 9, a = ceiling(n / 2)) C(9,n) x C(n, a)
static int arg2choice(int argc, char * * argv);
int main(int argc, char * * argv)
{
  // If argc is 1, all 6045 cases are printed
  // If argc is 2:
  //    argv[1] is "s": stop when the winner is known or definitely draw
  //    argv[1] is "e": eliminate rotation or mirror equivalent
  if (argc > 2) // should be only 1 or 2
    { return EXIT_FAILURE; }
  int choice = arg2choice(argc, argv);
  if (choice == 0) // unknown option
    { return EXIT_FAILURE; }
  Board * allboard = malloc(NUMBOARD * sizeof(Board));
  int ind;
  for (ind = 0; ind < NUMBOARD; ind ++)
    { initBoard(& allboard[ind]); }
  int numgen = generateBoard(allboard, choice);
  for (ind = 0; ind < numgen; ind ++)
    { printBoard(& allboard[ind], 1); }
  free (allboard);
  return EXIT_SUCCESS;
}
static int arg2choice(int argc, char * * argv)
{
  if (argc == 1) { return 1; }
  if (argc == 2)
    {
      if (strcmp(argv[1], "s") == 0) { return 2; }
      if (strcmp(argv[1], "e") == 0) { return 3; }
    }
  return 0;
}
