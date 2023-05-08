// CH19:listinsert.c
#include "list.h"
static Node * Node_construct(int val)
{
  Node * nd = malloc(sizeof(Node));
  nd -> value = val;
  nd -> next = NULL;
  return nd;
}
Node * List_insert(Node * head, int val) 
{ 
  printf("insert %d\n", val);
  Node * ptr = Node_construct(val); 
  ptr -> next = head; // insert new node before head
  return ptr;      // return the newly created node
}
