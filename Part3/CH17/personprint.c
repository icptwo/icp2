// CH17:personprint.c
#include "person.h"
#include <stdio.h>
void Person_print(Person * p)
{
  printf("Name: %s. ", p -> name);
  printf("Date of Birth: %d/%d/%d\n", p -> year, p -> month, p -> date);
}
