// CH27:decompress.c
#include <stdio.h>
#include "decompress.h"
#include "tree.h"
int decompress(char * infile, char * outfile, char * progressfile)
{
  // steps:
  // 1. read the tree
  // 2. read the length
  // 3. convert the codes to the letters
  FILE * pfptr = fopen(progressfile, "w");
  if (pfptr == NULL) // fopen fail
    { return 0; }
  FILE * infptr = fopen(infile, "r");
  if (infptr == NULL)
    { return 0; }
  TreeNode * tree = restoreCodeTree(infptr, pfptr);
  Tree_print(tree, 0, pfptr);    
  return Tree_leaf(tree);
}
