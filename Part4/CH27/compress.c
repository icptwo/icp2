// CH27:compress.c
// #include "compress.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bits.h"
#include "tree.h"
#include "list.h"
#include "occur.h"
#include "codebook.h"
static void buildCodeBookHelper(TreeNode * tn, CodeBook * cbook,
				int * row, int col);
static void buildCodeBook(TreeNode * root, CodeBook *  cbook);
static void printCodeBook(CodeBook * cbook, FILE * pfptr);
static void destroyCodeBook(CodeBook * cbook);
int compress(char * infile, char * outfile, char * progressfile)
{
  // steps:
  // 1. count the occurrences of the letters
  // 2. sort in the ascending order
  // 3. build the tree
  // 4. convert the tree into the code book
  // 5. replace the letters by the codes
  // step 1:
  CharOccur chararr [NUMCHAR];
  FILE * pfptr = fopen(progressfile, "w");
  if (pfptr == NULL) // fopen fail
    { return 0; }
  int total = countOccur(infile, chararr, NUMCHAR);
  if (total == 0) // nothing in the file
    { return 0; }
  // step 2:
  qsort(chararr, NUMCHAR, sizeof(CharOccur), compareOccur);
  // save the progress to a file
  printOccur(chararr, NUMCHAR, pfptr);
  // step 3:
  TreeNode * tree = buildCodeTree(chararr, NUMCHAR, pfptr);
  if (tree == NULL)
    { return EXIT_FAILURE; }
  // step 4:
  CodeBook * cbook = malloc(sizeof(CodeBook));
  buildCodeBook(tree, cbook);
  printCodeBook(cbook, pfptr);
  // encode(argv[2], argv[2], tree, codeBook);
  destroyCodeBook(cbook);
  return total;
}
static void buildCodeBookHelper(TreeNode * tn, CodeBook * cbook,
				int * row, int col)
{
  if (tn == NULL) // nothing to do
    { return; }
  // is it a leaf node?
  TreeNode * lc = tn -> left;
  TreeNode * rc = tn -> right;
  if ((lc == NULL) && (rc == NULL))
    {
      // finish one code
      cbook -> codes[*row][0] = tn -> ascii;
      (* row) ++;
      return;
    }
  if (lc != NULL)
    {
      // populate this column of the entire subtree
      int numRow = Tree_leaf(lc);
      int ind;
      for (ind = * row; ind < (* row) + numRow; ind ++)
	{ cbook -> codes[ind][col] = 0; }
      buildCodeBookHelper(lc, cbook, row, col + 1);
    }
  if (rc != NULL)
    {
      int numRow = Tree_leaf(rc);
      int ind;
      for (ind = * row; ind < (* row) + numRow; ind ++)
	{ cbook -> codes[ind][col] = 1; }
      buildCodeBookHelper(rc, cbook, row, col + 1);
    }    
}
static void buildCodeBook(TreeNode * root, CodeBook * cbook)
{
  int numRow = Tree_leaf(root);
  int numCol = Tree_height(root);
  numCol ++; // to accommodate the ending -1
  // column start at 1 because [0] stores the character
  cbook -> numRow = numRow;
  cbook -> numCol = numCol;
  cbook -> codes = malloc(sizeof(int*) * numRow);
  int row;
  for (row = 0; row < numRow; row ++)
    {
      cbook -> codes[row] = malloc(sizeof(int) * numCol);
      int col;
      // initialize to -1
      for (col = 0; col < numCol; col ++)
	{ cbook-> codes[row][col] = -1; }
    }
  row = 0;
  buildCodeBookHelper(root, cbook, & row, 1); 
}
static void destroyCodeBook(CodeBook * cbook)
{
  int ind;
  int numRow = cbook -> numRow;
  for (ind = 0; ind < numRow; ind ++)
    {
      if ((cbook -> codes[ind]) != NULL)
	{ free (cbook -> codes[ind]); }
    }
  free (cbook);
}
static void printCodeBook(CodeBook * cbook, FILE * pfptr)
{
  int row;
  int numRow = cbook -> numRow;
  for (row = 0; row < numRow; row ++)
    {
      // print the character
      fprintf(pfptr, "%c: ", cbook -> codes[row][0]);
      int col = 1;
      while (cbook -> codes[row][col] != -1)
	{
	  fprintf(pfptr, "%d ", cbook -> codes[row][col]);
	  col ++;
	}
      fprintf(pfptr, "\n");
    }
}
