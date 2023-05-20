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
static void encodeFile(char * infile, char * outfile,
		       CodeBook * cbook, TreeNode * tree);
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
  // step 5:
  encodeFile(infile, outfile, cbook, tree);
  Tree_destroy(tree);
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
static void encodeFile(char * infile, char * outfile,
		       CodeBook * cbook, TreeNode * tree)
{
  FILE * inptr = fopen(infile, "r");
  if (inptr == NULL)
    { return; }
  FILE * outptr = fopen(outfile, "w");
  if (outptr == NULL)
    { return; }
  // save the tree in the output file
  Tree_save(tree, outptr);
  // find the length of the file
  fseek(inptr, 0, SEEK_END);
  int length = ftell(inptr);
  // save the file length in the output file
  fwrite(& length, sizeof(int), 1, outptr);
  // find each ASCII's index in the code book
  int ASCII2code[NUMCHAR] = {-1};
  int numRow = cbook -> numRow;
  int row;
  for (row = 0; row < numRow; row ++)
    {
      int ascii = cbook -> codes[row][0];
      ASCII2code[ascii] = row;
    }
  // convert the letters from the input and save in the output file
  fseek(inptr, 0, SEEK_SET); // go back to the beginning of the file
  int count = 0;
  unsigned char whichbit = 0;
  unsigned char curbyte  = 0;
  while (! feof(inptr))
    {
      int ch = fgetc(inptr);
      if (ch != EOF)
	{
	  row = ASCII2code[ch];
	  int col = 0;
	  while (cbook -> codes[row][col] != -1)
	    {
	      writeBit(outptr, cbook -> codes[row][col],
		       & whichbit, & curbyte);
	      col ++;
	    }
	  count ++;
	}
    }
  if (count != length)
    { printf("count = %d, length = %d\n", count, length); }
  padZero(outptr, & whichbit, & curbyte);
  fclose (inptr);
  fclose (outptr);
}
