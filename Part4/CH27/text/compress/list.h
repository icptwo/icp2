// list.h
#ifndef LIST_H
#define LIST_H
#include "tree.h"
#include "occur.h"
#include <stdio.h>
typedef struct listnode
{
  struct listnode * next;
  TreeNode * tnptr;
} ListNode;
ListNode * List_insertChar(ListNode *, char, int);
ListNode * List_insertTree(ListNode *, TreeNode * tp);
void List_print(ListNode * head);
void List_destroy(ListNode * head);
#endif
