// CH27:list.h
#ifndef LIST_H
#define LIST_H
#include "tree.h"
#include "occur.h"
#include <stdio.h>
#include <stdbool.h>
typedef struct listnode
{
  struct listnode * next;
  TreeNode * tnptr;
} ListNode;
ListNode * List_insertChar(ListNode *, char, int);
ListNode * List_insertTree(ListNode *, TreeNode * tp, bool order);
void List_print(ListNode * head, FILE * pfptr);
void List_destroy(ListNode * head);
#endif
