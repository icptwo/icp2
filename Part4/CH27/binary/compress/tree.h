// CH27:binary:compress:tree.h
#ifndef TREE_H
#define TREE_H
#include <stdio.h>
typedef struct treenode
{
  struct treenode * left;
  struct treenode * right;
  char ascii; 
  int  occur; 
} TreeNode;
TreeNode * Tree_create(char val, int occur);
TreeNode * Tree_merge(TreeNode * tree1, TreeNode * tree2);
void Tree_print(TreeNode * tree, int level); 
void Tree_destroy(TreeNode * tree);
int Tree_height(TreeNode * tree);
void Tree_save(TreeNode * tree, FILE * fptr);
 #endif
