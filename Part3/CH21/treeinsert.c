// treeinsert.c
#include "tree.h"
#include <stdlib.h>
static TreeNode * TreeNode_construct(int val)
{
  TreeNode * tn;
  tn = malloc(sizeof(TreeNode));
  tn -> left = NULL;
  tn -> right = NULL;
  tn -> value = val;
  return tn;
}
TreeNode * Tree_insert(TreeNode * tn, int val)
{
  if (tn == NULL)
    { return TreeNode_construct(val); } // empty, create a node
  if (val == (tn -> value))
    { return tn; } // do not insert the same value
  if (val < (tn -> value)) // go to the left side 
    { tn -> left = Tree_insert(tn -> left, val); }
  else // go to the right side
    { tn -> right = Tree_insert(tn -> right, val); }
  return tn;
}
