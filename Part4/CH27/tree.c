// CH27:tree.c
#include "tree.h"
#include "bits.h"
#include "list.h"
#include <stdlib.h>
#include <stdbool.h>
TreeNode * buildCodeTree(CharOccur * chararr, int length, FILE * pfptr)
{
  ListNode * head = NULL;
  int ind;
  // build the list with ascending order
  for (ind = 0; ind < length; ind ++)
    {
      CharOccur * optr = & chararr[ind];
      if ((optr -> occur) != 0)
	{
	  head = List_insertChar(head, optr -> ascii, optr -> occur);
	}
    }
  List_print(head, pfptr);
  // merge the nodes and build the tree
  while ((head -> next) != NULL)
    {
      TreeNode * tree1 = head -> tnptr;
      TreeNode * tree2 = (head -> next) -> tnptr;
      TreeNode * tp  = Tree_merge(tree1, tree2);
      ListNode * p = head;
      ListNode * q = head -> next;
      head = List_insertTree(q -> next, tp, true);
      free (p);
      free (q);
    }
  List_print(head, pfptr);
  TreeNode * tree = head -> tnptr;
  free (head); // list no longer needed
  return tree;
}
TreeNode * Tree_create(char val, int occur)
{
  TreeNode * tree = malloc(sizeof(TreeNode));
  tree -> left = NULL;
  tree -> right = NULL;
  tree -> ascii = val;
  tree -> occur = occur;
  return tree;
}
// post-order
void Tree_print(TreeNode * tree, int level, FILE * pfptr)
{
  if (tree == NULL) { return; }
  TreeNode * lc = tree -> left;  // left child
  TreeNode * rc = tree -> right; // right child
  Tree_print(lc, level + 1, pfptr);
  Tree_print(rc, level + 1, pfptr);
  int depth;
  for (depth = 0; depth < level; depth ++)
    { fprintf(pfptr, "    "); }
  fprintf(pfptr, "occur = %d ", tree -> occur);
  if ((lc == NULL) && (rc == NULL)) // leaf node
    {
      fprintf(pfptr, "ascii = %d, '%c'", tree -> ascii, tree -> ascii);
    } 
  fprintf(pfptr, "\n");
}
void Tree_destroy(TreeNode * tree)
{
  if (tree == NULL) { return; }
  Tree_destroy(tree -> left);
  Tree_destroy(tree -> right);
  free (tree);
}
TreeNode * Tree_merge(TreeNode * tree1, TreeNode * tree2)
{
  TreeNode * parent =
    Tree_create(0, (tree1 -> occur) + (tree2 -> occur));
  parent -> left = tree1;
  parent -> right = tree2;
  return parent;
}
int Tree_height(TreeNode * tree)
{
  if (tree == NULL) { return 0; }
  int left = Tree_height(tree -> left);
  int right = Tree_height(tree -> right);
  if (left > right) { return (left + 1); }
  return (right + 1);
}
int Tree_leaf(TreeNode * tree)
{
  if (tree == NULL)
  { return 0; }
  if (((tree -> left) == NULL) &&
      ((tree -> right) == NULL))
    { return 1; }
  int numLeft = Tree_leaf(tree -> left);
  int numRight = Tree_leaf(tree -> right);
  return (numLeft + numRight);
}
static void Tree_saveHelper(TreeNode * tree, FILE * fptr,
			    unsigned char * whichbit,
			    unsigned char * curbyte)
{
  if (tree == NULL) { return; }
  TreeNode * lc = tree -> left;  // left child
  TreeNode * rc = tree -> right; // right child
  Tree_saveHelper(lc, fptr, whichbit, curbyte);
  Tree_saveHelper(rc, fptr, whichbit, curbyte);
  if ((lc == NULL) && (rc == NULL)) // leaf node
    {
      writeBit(fptr, 1, whichbit, curbyte);
      writeByte(fptr, tree -> ascii, whichbit, curbyte);
    } 
  else { writeBit(fptr, 0, whichbit, curbyte); }
}
void Tree_save(TreeNode * tree, FILE * fptr)
{
  if (tree == NULL) { return; }
  unsigned char whichbit = 0;
  unsigned char curbyte = 0;
  Tree_saveHelper(tree, fptr, & whichbit, & curbyte);
  writeBit(fptr, 0, & whichbit, & curbyte);
  padZero(fptr, & whichbit, & curbyte);
  writeByte(fptr, '\n', & whichbit, & curbyte);
}
TreeNode * restoreCodeTree(FILE * infptr, FILE * pfptr)
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
	  TreeNode * tn = Tree_create(byte, -1); // occur does not matter
	  fprintf(pfptr, "1%c", byte);
	  head = List_insertTree(head, tn, false);
	}
      if (bit == 0)
	{
	  numZero ++;
	  fprintf(pfptr, "0");
	  if ((head != NULL) && ((head -> next) != NULL))
	    {
	      // merge the most recent two tree nodes
	      TreeNode * tree1 = head -> tnptr;
	      TreeNode * tree2 = (head -> next) -> tnptr;
	      TreeNode * tp  = Tree_merge(tree2, tree1); // note the order
	      ListNode * p = head;
	      ListNode * q = head -> next;
	      head = List_insertTree(q -> next, tp, false);
	      free (p);
	      free (q);
	    }
	}
      if (numOne == numZero)
	{ finishedtree = true; }
    }
  TreeNode * tree = head -> tnptr;
  free (head);
  removePad(infptr, & whichbit, & curbyte);
  readByte(infptr, & byte, & whichbit, & curbyte); // should be '\n'
  if (byte != '\n')
    { printf("wrong format\n"); }
  fprintf(pfptr, "\n");
  return tree;
}
