// CH11:security1.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char * * argv)
{
  char dest[5];
  dest[-3] = 'M';
  dest[0] = 'C';
  dest[1] = '-';
  dest[2] = 'P';
  dest[3] = 'R';
  dest[4] = 'O';  
  dest[5] = '\0';
  printf("%s\n", dest);
  return EXIT_SUCCESS;
}
