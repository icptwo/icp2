// CH20:listreverse.c
#include "list.h"
Node * List_reverse(Node * head)
{
  if (head == NULL) { return NULL; } // empty list, nothing to do
  Node * orighead = head;
  Node * revhead = NULL; // must initialize to NULL
  Node * origsec; // will be assigned before using
  while (orighead != NULL)
    {
      origsec = orighead -> next;
      orighead -> next = revhead;
      revhead = orighead;
      orighead = origsec;
    }
  return revhead;
}
