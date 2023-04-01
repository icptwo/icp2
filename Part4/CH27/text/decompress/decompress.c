// decompress.c
#include "decompress.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define NUMCHAR 128
TreeNode * buildTree(FILE * infptr)
{
  bool finishedtree = false;
  int numOne  = 0;
  int numZero = 0;
  ListNode * head = NULL;
  while (finishedtree == false)
    {
      int ctrl = fgetc(infptr);
      // printf("ctrl = %c\n", ctrl);
      if (ctrl == '1')
	{
	  numOne ++;
	  int ascii = fgetc(infptr);
	  // printf("ascii = %c\n", ascii);	  
	  if (ascii == EOF) { printf("wrong format, EOF\n"); }
	  TreeNode * tn = Tree_create(ascii);
	  head = List_insertTree(head, tn);
	}
      if (ctrl == '0')
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
  // Tree_print(tree, 0);
  int ch = fgetc(infptr); // remove \n
  if (ch != '\n') { printf("wrong format\n"); }
  return tree;
}
void decode(FILE * infptr, char * outfile, int length, TreeNode * tree)
{
  FILE * outfptr = fopen(outfile, "w");
  if (outfptr == NULL) { return; }
  TreeNode * tn = tree;
  while (length > 0)
    {
      int code = fgetc(infptr);
      if (code != EOF)
	{
	  if (code == '0') { tn = tn -> left; }
	  if (code == '1') { tn = tn -> right; }
	  if ((tn -> left) == NULL) // leaf node
	    {
	      fprintf(outfptr, "%c", tn -> ascii);
	      tn = tree; // return to the top
	      length --;
	    }
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
  fscanf(infptr, "%d\n", & length);
  // printf("length = %d\n", length);
  decode(infptr, argv[2], length, tree);
  fclose (infptr);
  Tree_destroy(tree);
  return EXIT_SUCCESS;
}

