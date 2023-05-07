// CH17:person3.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "person.h"
int main(int argc, char * argv[])
{
  Person * p1 = Person_construct(1989, 8, 21, "Amy");
  Person * p2 = Person_construct(1991, 2, 17, "Bob");
  p2 = p1;  // discard memory for Bob, leak memory
  Person_print(p1);
  Person_print(p2);
  Person_destruct(p1);
  Person_destruct(p2); // will cause problem
  return EXIT_SUCCESS;
}
