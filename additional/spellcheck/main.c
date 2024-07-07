// ***
// *** You must modify this file
// ***

#include <stdio.h>  
#include <stdlib.h> 
#include <string.h> 
#include <stdbool.h>
#include "checker.h"

int main(int argc, char * * argv)
{
  if (argc < 3)
    { return EXIT_FAILURE; }
  int numword = countWords(argv[1]);
  if (numword <= 0) // empty dictionary or some words too long
    { return EXIT_FAILURE; }
  WordDistance * wd = malloc(sizeof(WordDistance) * numword);
  if (wd == NULL)
    { return EXIT_FAILURE; }
  bool rtv = readWords(argv[1], wd, numword);
  if (rtv == false)
    { return EXIT_FAILURE; }
  calculateDistance(wd, numword, argv[2]);
  sortDistance(wd, numword);
  printWord(wd, numword);
  return EXIT_SUCCESS;
}

