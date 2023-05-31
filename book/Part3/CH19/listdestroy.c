// CH19:listdestroy.c
#include "list.h"
#include <stdlib.h>
void List_destroy(Node * head)
{
  while (head != NULL)
    {
      Node * p = head -> next;
      free (head);
      head = p;
    }
}
