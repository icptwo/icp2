// list.h
#ifndef LIST_H
#define LIST_H
#include "tree.h"
#include <stdio.h>
typedef struct listnode
{
  struct listnode * next;
  TreeNode * tnptr;
} ListNode;
ListNode * List_insertTree(ListNode *, TreeNode * tp);
void List_destroy(ListNode * head);
#endif
