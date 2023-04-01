// list.c
#include "list.h"
#include <stdlib.h>
static ListNode * ListNode_create(TreeNode * tn)
{
  ListNode * ln = malloc(sizeof(ListNode));
  ln -> next = NULL;
  ln -> tnptr = tn;
  return ln;
}
ListNode * List_insertTree(ListNode * head, TreeNode * tn)
// insert at the beginning, do not sort
{
  ListNode * ln = ListNode_create(tn);
  ln -> next = head;
  return ln;
}
void List_destroy(ListNode * head)
{
  if (head == NULL) { return; }
  ListNode * p = head;
  while (head != NULL)
    {
      p = head -> next;
      Tree_destroy(head -> tnptr);
      free (head);
      head = p;
    }
}
