// CH27:list.c
#include "list.h"
#include <stdlib.h>
static ListNode * ListNode_create(TreeNode * tn)
{
  ListNode * ln = malloc(sizeof(ListNode));
  ln -> next = NULL;
  ln -> tnptr = tn;
  return ln;
}
ListNode * List_insertTree(ListNode * head, TreeNode * tn, bool order)
// if order is true, insert in ascending order
// if order is false, insert at the beginning
{
  ListNode * ln = ListNode_create(tn);
  if (head == NULL) // empty list, create first list node
    { return ln; } 
  // insert in the ascending order
  int occur = tn -> occur;
  if ((order == false) ||
      (occur < ((head -> tnptr) -> occur))) // at the beginning
    {
      ln -> next = head;
      return ln;
    }
  // p is always before q
  ListNode * p = head;
  ListNode * q = p -> next;
  // find where to insert, ascending order
  while ((q != NULL) && ((q -> tnptr) -> occur) < occur)
    {
      p = p -> next;
      q = q -> next;
    }
  // does not matter whether q is NULL or not
  p -> next = ln;
  ln -> next = q; 
  return head;  
}
ListNode * List_insertChar(ListNode * head, char val, int occur)
{
  TreeNode * tn = Tree_create(val, occur);
  return List_insertTree(head, tn, true);
}
void List_print(ListNode * head, FILE * pfptr)
{
  if (head == NULL) { return; }
  Tree_print(head -> tnptr, 0, pfptr);
  List_print(head -> next, pfptr);
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
