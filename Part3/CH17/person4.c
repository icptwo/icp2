// CH17:person4.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "person.h"
int main(int argc, char * argv[])
{
  Person p1; // object, not a pointer
  Person p2; // object, not a pointer
  p1.year = 1989;
  p1.month = 8;
  p1.date = 21;
  p1.name = strdup("Amy");
  p2.year = 1991;
  p2.month = 2;
  p2.date = 17;
  p2.name = strdup("Bob");
  Person_print(& p1);
  Person_print(& p2);
  p2 = p1; // p1 and p2 store the same address
  Person_print(& p1);
  Person_print(& p2);
  free (p1.name);
  free (p2.name); // free the same memory twice
  return EXIT_SUCCESS;
}
