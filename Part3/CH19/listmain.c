// CH19:listmain.c
#include "list.h"
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char * argv[])
{
  Node * head = NULL; /* must initialize it to NULL */
  head = List_insert(head, 917);
  head = List_insert(head, -504);
  head = List_insert(head, 326);
  List_print(head);
  head = List_delete(head, -504);
  List_print(head);
  head = List_insert(head, 138);
  head = List_insert(head, -64);
  head = List_insert(head, 263);
  List_print(head);
  if (List_search(head, 138) != NULL)
    { printf("138 is in the list\n"); }
  else
    { printf("138 is not in the list\n"); }
  if (List_search(head, 987) != NULL)
    { printf("987 is in the list\n"); }
  else
    { printf("987 is not in the list\n"); }
  head = List_delete(head, 263); // delete the first Node
  List_print(head);
  head = List_delete(head, 917); // delete the last Node 
  List_print(head);
  List_destroy(head);   // delete all Nodes 
  return EXIT_SUCCESS;
}
