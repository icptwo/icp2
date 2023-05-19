// CH27:compress.c
// #include "compress.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bits.h"
#include "tree.h"
#include "list.h"
#include "occur.h"
int compress(char * infile, char * outfile, char * progressfile)
{
  CharOccur chararr [NUMCHAR];
  FILE * pfptr = fopen(progressfile, "w");
  if (pfptr == NULL) // fopen fail
    { return 0; }
  int total = countOccur(infile, chararr, NUMCHAR, pfptr);
  if (total == 0) // nothing in the file
    { return 0; }
  /*
  TreeNode * tree = buildTree(chararr);
  if (tree == NULL)
    { return EXIT_FAILURE; }
    char * codeBook[NUMCHAR] = {NULL};
    buildCodeBook(tree, codeBook);
    printCodeBook(codeBook);
    encode(argv[2], argv[2], tree, codeBook);
    destroyCodeBook(codeBook);
  */
  return total;
}
