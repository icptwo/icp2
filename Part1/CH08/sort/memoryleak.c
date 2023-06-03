// CH08:sort/memoryleak.c
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char * * argv)
{
  char * cptr;
  cptr = malloc(sizeof(char) * 100);
  if (cptr == NULL)
    {
      return EXIT_FAILURE;
    }
  // free (cptr); // leak memory
  return EXIT_SUCCESS;
}
