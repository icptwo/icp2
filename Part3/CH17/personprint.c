// CH17:personprint.c
#include "person.h"
#include <stdio.h>
void Person_print(Person * p)
{
  printf("Date of Birth: %d/%d/%d\n", p -> year, p -> month, p -> date);
  printf("Name: %s. ", p -> name);
}
