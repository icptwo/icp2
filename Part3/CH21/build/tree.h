// CH21:build/tree.h
#ifndef TREE_H
#define TREE_H
typedef struct tnode
{
  int value;
  struct tnode * left;
  struct tnode * right;
} TreeNode;
TreeNode * buildTree(int * inArray, int * postArray, int size);
void postOrder(TreeNode * tr, char * filename);
void inOrder(TreeNode * tr, char * filename);
void preOrder(TreeNode * tr, char * filename);
void printTree(TreeNode * tr); // inorder, add space for easier reading
void destroyTree(TreeNode * tr);
TreeNode * insertNode(TreeNode * tr, int val);
#endif
