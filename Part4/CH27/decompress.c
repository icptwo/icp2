// CH27:binary:decompress:decompress.c
#include "decompress.h"
#include "bits.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define NUMCHAR 128
TreeNode * buildTree(FILE * infptr)
{
  bool finishedtree = false;
  int numOne  = 0;
  int numZero = 0;
  unsigned char bit;
  unsigned char byte;
  unsigned char whichbit = 0;
  unsigned char curbyte  = 0;
  ListNode * head = NULL;
  while (finishedtree == false)
    {
      readBit(infptr, & bit, & whichbit, & curbyte);
      if (bit == 1)
	{
	  numOne ++;
	  readByte(infptr, & byte, & whichbit, & curbyte);
	  // printf("1%c\n", byte);
	  TreeNode * tn = Tree_create(byte);
	  head = List_insertTree(head, tn);
	}
      if (bit == 0)
	{
	  numZero ++;
	  if ((head != NULL) && ((head -> next) != NULL))
	    {
	      // merge the most recent two tree nodes
	      TreeNode * tree1 = head -> tnptr;
	      TreeNode * tree2 = (head -> next) -> tnptr;
	      TreeNode * tp  = Tree_merge(tree2, tree1); // note the order
	      ListNode * p = head;
	      ListNode * q = head -> next;
	      head = List_insertTree(q -> next, tp);
	      free (p);
	      free (q);
	    }
	}
      if (numOne == numZero) { finishedtree = true; }
    }
  TreeNode * tree = head -> tnptr;
  free (head);
  removePad(infptr, & whichbit, & curbyte);
  readByte(infptr, & byte, & whichbit, & curbyte); // should be '\n'
  if (byte != '\n') { printf("wrong format\n"); }
  return tree;
}
void decode(FILE * infptr, char * outfile, int length, TreeNode * tree)
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
int main(int argc, char * * argv)
{
  if (argc != 3) { return EXIT_FAILURE; }
  // argv[1]: input file name
  // argv[2]: output file name
  FILE * infptr = fopen(argv[1], "r");
  if (infptr == NULL) { return EXIT_FAILURE; }
  TreeNode * tree = buildTree(infptr);
  if (tree == NULL) { return EXIT_FAILURE; }
  int length;
  if (fread(& length, sizeof(int), 1, infptr) != 1)
    { printf("wrong format\n"); }
  // printf("length = %d\n", length);
  unsigned char newline;
  fread(& newline, sizeof(unsigned char), 1, infptr);
  if (newline != '\n') 
    { printf("wrong format\n"); }
  decode(infptr, argv[2], length, tree);
  fclose (infptr);
  Tree_destroy(tree);
  return EXIT_SUCCESS;
}
