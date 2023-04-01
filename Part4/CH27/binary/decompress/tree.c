// CH27:binary:decompress:tree.c
#include "tree.h"
#include <stdlib.h>
TreeNode * Tree_create(char ascii)
{
  TreeNode * tree = malloc(sizeof(TreeNode));
  tree -> left = NULL;
  tree -> right = NULL;
  tree -> ascii = ascii;
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
  if ((lc == NULL) && (rc == NULL))
    { printf("ascii = %d, '%c'", tree -> ascii, tree -> ascii); } // leaf node
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
  TreeNode * parent = Tree_create(0);
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

static void Tree_saveHelper(TreeNode * tree, FILE * fptr)
{
  if (tree == NULL) { return; }
  TreeNode * lc = tree -> left;  // left child
  TreeNode * rc = tree -> right; // right child
  Tree_saveHelper(lc, fptr);
  Tree_saveHelper(rc, fptr);
  if ((lc == NULL) && (rc == NULL))
    { fprintf(fptr, "1%c", tree -> ascii); } // leaf node
  else { fprintf(fptr, "0"); }
}

void Tree_save(TreeNode * tree, FILE * fptr)
{
  if (tree == NULL) { return; }
  Tree_saveHelper(tree, fptr);
  fprintf(fptr, "0\n"); // ending 0 with a new line
}
