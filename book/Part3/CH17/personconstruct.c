// CH17:personconstruct.c
#include "person.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
Person * Person_construct(int y, int m, int d, char * n)
{
  Person * p = NULL;
  p = malloc(sizeof(Person));
  if (p == NULL) { return NULL; } // malloc fail
  p -> year = y;
  p -> month = m;
  p -> date = d;
  p -> name = strdup(n); // malloc + strcpy
  if ((p -> name) == NULL) // malloc fail
    {
      free (p);
      return NULL;
    }
  strcpy(p -> name, n);
  return p;
}
