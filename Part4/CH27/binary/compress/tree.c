// CH27:binary:compress:tree.c
#include "tree.h"
#include "bits.h"
#include <stdlib.h>
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
void Tree_print(TreeNode * tree, int level)
{
  if (tree == NULL) { return; }
  TreeNode * lc = tree -> left;  // left child
  TreeNode * rc = tree -> right; // right child
  Tree_print(lc, level + 1);
  Tree_print(rc, level + 1);
  int depth;
  for (depth = 0; depth < level; depth ++) { printf("    "); }
  printf("occur = %d ", tree -> occur);
  if ((lc == NULL) && (rc == NULL)) // leaf node
    { printf("ascii = %d, '%c'", tree -> ascii, tree -> ascii); } 
  printf("\n");
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
  TreeNode * parent = Tree_create(0, (tree1 -> occur) + (tree2 -> occur));
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
