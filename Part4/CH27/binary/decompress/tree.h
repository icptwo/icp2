// CH27:binary:decompress:tree.h
#ifndef TREE_H
#define TREE_H
#include <stdio.h>
typedef struct treenode
{
  struct treenode * left;
  struct treenode * right;
  char ascii; 
} TreeNode;
TreeNode * Tree_create(char ascii);
TreeNode * Tree_merge(TreeNode * tree1, TreeNode * tree2);
void Tree_print(TreeNode * tree, int level); 
void Tree_destroy(TreeNode * tree);
#endif
