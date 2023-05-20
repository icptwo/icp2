// CH27:tree.h
#ifndef TREE_H
#define TREE_H
#include <stdio.h>
#include "occur.h"
typedef struct treenode
{
  struct treenode * left;
  struct treenode * right;
  char ascii; 
  int  occur; 
} TreeNode;
TreeNode * buildCodeTree(CharOccur * chararr, int length, FILE * pfptr);
TreeNode * restoreCodeTree(FILE * infptr, FILE * pfptr);
TreeNode * Tree_create(char val, int occur);
TreeNode * Tree_merge(TreeNode * tree1, TreeNode * tree2);
void Tree_print(TreeNode * tree, int level, FILE * pfptr); 
void Tree_destroy(TreeNode * tree);
int Tree_height(TreeNode * tree);
int Tree_leaf(TreeNode * tree);
void Tree_save(TreeNode * tree, FILE * fptr);
 #endif
