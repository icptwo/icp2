#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "sudoku.h"
int main(int argc, char * * argv)
{
  // argv[1]: "f"- input from a file, "n"- from network
  // argv[2]: if argv[1] is "f"- input file name
  //          if argv[1] is "n"- host name of network
  // argv[3]: if argv[1] is "f"- output file name
  //          if argv[1] is "n"- network port
  if (argc < 4)  { return EXIT_FAILURE; }
  if ((strcmp(argv[1], "f") != 0) && (strcmp(argv[1], "n") != 0))
    { return EXIT_FAILURE; }
  Sudoku sud;
  bool rtv = false;
  int servsock;
  if (strcmp(argv[1], "f") == 0)
    { rtv = fileSudoku(argv[2], & sud); }
  else
    {
      if (strcmp(argv[1], "n") == 0)
	{
	  int port = strtol(argv[3], NULL, 10);
	  rtv = networkSudoku(argv[2], port, & sud, & servsock);
	}
      else { return EXIT_FAILURE; } // neither "f" nor "n"
    }
  if (rtv == false) { return EXIT_FAILURE; }
  solveSudoku(& sud);
  printSudoku(& sud);
  if (strcmp(argv[1], "f") == 0)
    { saveSudoku(argv[3], & sud); }
  else
    { sendSudoku(servsock, & sud); }
  return EXIT_SUCCESS;
}

