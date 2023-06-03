// CH21:build/tree.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
static TreeNode * buildTreeHelper(int * inArray, int * postArray,
				  int inStart, int inEnd, int * postIndex);
// find the index of val inside the array, assume the array's elements
// are distinct but the values may not be sorted
static int findIndex(int * arr, int start, int end, int val);
TreeNode * buildTree(int * inArray, int * postArray, int size)
{
  TreeNode * tn = NULL;
  int postIndex = size - 1;
  tn = buildTreeHelper(inArray, postArray, 0, size - 1, & postIndex);
  return tn;
}
// The algorithm here is from
// https://www.geeksforgeeks.org/
// construct-a-binary-tree-from-postorder-and-inorder/
static TreeNode * buildTreeHelper(int * inArray, int * postArray,
				  int inStart, int inEnd, int * postIndex)
{
  if (inStart > inEnd)
    { return NULL; } // empty array, nothing to build
  // find the last node in post order, it is the root
  int value = postArray[* postIndex];
  TreeNode * tn = NULL;
  tn = insertNode(tn, value);
  (* postIndex) --; // move index back by one, make sure to use ()
  if (inStart == inEnd)
    { return tn; } // only one node
  int ind = findIndex(inArray, inStart, inEnd, value);
  if (ind == -1)
    {
      fprintf(stderr, "SOMETHING WRONG\n");
      return NULL;
    }
  // ind divides the arrays into left subtree and right subtree
  // build the subtrees separately
  // need to build the right subtree first so that postIndex is updated
  tn -> right = buildTreeHelper(inArray, postArray, ind + 1,
				inEnd, postIndex);
  tn -> left = buildTreeHelper(inArray, postArray, inStart,
			       ind - 1, postIndex);
  return tn;
}
static TreeNode * createTreeNode(int val)
{
  TreeNode * tr = malloc(sizeof(TreeNode));
  tr -> value = val;
  tr -> left  = NULL;
  tr -> right = NULL;
  return tr;
}
TreeNode * insertNode(TreeNode * tn, int val)
{
  if (tn == NULL)
    { return createTreeNode(val); }
  if ((tn -> value) == val)
    { return tn; } // disallow same value twice
  if ((tn -> value) > val)
    {
      // go to left
      tn -> left = insertNode(tn -> left, val);
      return tn;
    }
  // go to right
  tn -> right = insertNode(tn -> right, val);
  return tn;
}
void destroyTree(TreeNode * tn)
{
  if (tn == NULL)
    { return; }
  destroyTree (tn -> left);
  destroyTree (tn -> right);
  free (tn);
}
static void postOrderHelper(TreeNode * tn, FILE * fptr)
{
  if (tn == NULL)
    { return; }
  postOrderHelper(tn -> left, fptr);
  postOrderHelper(tn -> right, fptr);
  fprintf(fptr, "%d\n", tn -> value);
}
void postOrder(TreeNode * tn, char * filename)
{
  if (tn == NULL)
    { return; }
  FILE * fptr = fopen(filename, "w");
  postOrderHelper(tn, fptr);
  fclose (fptr);
}
static void inOrderHelper(TreeNode * tn, FILE * fptr)
{
  if (tn == NULL)
    { return; }
  inOrderHelper(tn -> left, fptr);
  fprintf(fptr, "%d\n", tn -> value);
  inOrderHelper(tn -> right, fptr);
}
void inOrder(TreeNode * tn, char * filename)
{
  if (tn == NULL)
    { return; }
  FILE * fptr = fopen(filename, "w");
  inOrderHelper(tn, fptr);
  fclose (fptr);
}
static void preOrderHelper(TreeNode * tn, FILE * fptr)
{
  if (tn == NULL)
    { return; }
  fprintf(fptr, "%d\n", tn -> value);
  preOrderHelper(tn -> left, fptr);
  preOrderHelper(tn -> right, fptr);
}
void preOrder(TreeNode * tn, char * filename)
{
  if (tn == NULL)
    { return; }
  FILE * fptr = fopen(filename, "w");
  preOrderHelper(tn, fptr);
  fclose (fptr);
}
static int findIndex(int * arr, int start, int end, int val)
{
  int ind = start;
  while (ind <= end)
    {
      if (arr[ind] == val)
	{ return ind; } // found
      ind ++;
    }
  return -1; // cannot find
}
static void printTreeHelper(TreeNode * tn, int level)
{
  if (tn == NULL)
    { return; }
  printTreeHelper(tn -> right, level + 1);
  int ind;
  // add space to show the nodes' levels
  for (ind = 0; ind < level; ind ++)
    { printf("     "); }
  printf("%d\n", tn -> value);
  printTreeHelper(tn -> left, level + 1);
}
void printTree(TreeNode * tn) 
{
  printTreeHelper(tn, 0);
}
