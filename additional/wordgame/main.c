// ***
// *** DO NOT modify this file
// ***

#include <stdio.h>  
#include <stdlib.h> 
#include <string.h> 
#include <stdbool.h>
#include "table.h"
#define LINELENGTH 80

int main(int argc, char * * argv)
{
  // argv[1] can be "-d" or "-f"
  // "-d" means argv[2] is a directory
  // "-f" means argv[2] is a file
  // argv[2] is a directory or a file
  // argv[3] is a letter (between "a" and "z")
  // argv[4] (optional) "-t" prints the table
  int charTable[NUMROW][NUMCOL];
  // row: letter 'a' to 'z'
  // column: count of letter following, last is space
  // [0][1]: how many times letter 'a' followed by 'b'
  // [1][4]: how many times letter 'b' followed by 'e'
  // [2][26]: how many times letter 'c' followed by space
  if ((argc != 4) && (argc != 5))
    {
      return EXIT_FAILURE;
    }
  if (strcmp(argv[1], "-d") == 0)
    {
      buildTable(argv[2], FROMDIR, charTable);
    }
  else if (strcmp(argv[1], "-f") == 0)
    {
      buildTable(argv[2], FROMFILE, charTable);
    }
  else
    {
      return EXIT_FAILURE;
    }
  completeWord(argv[3], charTable);
  if ((argc == 5) && (strcmp(argv[4], "-t") == 0))
    {
      printTable(charTable);
    }
  return EXIT_SUCCESS;
}

