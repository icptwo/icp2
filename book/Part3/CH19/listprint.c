// CH19:listprint.c
#include "list.h"
#include <stdio.h>
void List_print(Node * head)
{
  printf("\nPrint the whole list:\n");
  while (head != NULL)
    {
      printf("%d ", head -> value);
      head = head -> next;
    }
  printf("\n");
}
