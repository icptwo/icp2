// CH27:decompress.c
#include <stdio.h>
#include "decompress.h"
#include "tree.h"
#include "bits.h"
static void decodeFile(FILE * infptr, char * outfile,
		       int length, TreeNode * tree);
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
  int length;
  if (fread(& length, sizeof(int), 1, infptr) != 1)
    { fprintf(pfptr, "wrong format\n"); }
  fprintf(pfptr, "%d\n", length);
  unsigned char newline;
  if (fread(& newline, sizeof(unsigned char), 1, infptr) != 1)
    { fprintf(pfptr, "wrong format\n"); }
  if (newline != '\n')
    { fprintf(pfptr, "wrong format\n"); }
  decodeFile(infptr, outfile, length, tree);
  fclose(infptr);
  fclose(pfptr);
  Tree_destroy(tree);
  return length;
}
static void decodeFile(FILE * infptr, char * outfile,
		       int length, TreeNode * tree)
{
  FILE * outfptr = fopen(outfile, "w");
  if (outfptr == NULL) { return; }
  unsigned char bit;
  unsigned char whichbit = 0;
  unsigned char curbyte  = 0;
  TreeNode * tn = tree;
  while (length > 0)
    {
      readBit(infptr, & bit, & whichbit, & curbyte);
      if (bit == 0) { tn = tn -> left; }
      if (bit == 1) { tn = tn -> right; }
      if ((tn -> left) == NULL) // leaf node
	{
	  fprintf(outfptr, "%c", tn -> ascii);
	  tn = tree; // return to the top
	  length --;
	}
    }
  fclose (outfptr);
}
