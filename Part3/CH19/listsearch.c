// CH19:listsearch.c
#include "list.h"
#include <stdio.h>
Node * List_search(Node * head, int val)
// head: the head node of the linked list
// val: the value to search
// If any node stores val, this function returns that node
// If multiple nodes store val, this function returns the node
//    closest to the head.
// If no node stores val, this function returns NULL
{
  Node * ptr = head;
  while (ptr != NULL)
    {
      if ((ptr -> value) == val)
	{ return ptr;}
      ptr = ptr -> next;
    }
  return ptr; // must be NULL now
}
