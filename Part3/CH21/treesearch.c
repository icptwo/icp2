// treesearch.c
#include "tree.h"
TreeNode * Tree_search(TreeNode * tn, int val)
{
  if (tn == NULL) { return NULL; } // cannot find 
  if (val == (tn -> value)) { return tn; } // found 
  if (val < (tn -> value))
    { return Tree_search(tn -> left, val); } // search the left side 
  return Tree_search(tn -> right, val);
}

