// CH11:security2.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char * * argv)
{
  char str1[5];
  char str2[5];
  char dest[5];
  strcpy(str1, "ABC\n");
  strcpy(str2, "XYZ\n");
  printf("%s", str1);
  printf("%s", str2);
  dest[-3] = 'M';
  dest[0] = 'C';
  dest[1] = '-';
  dest[2] = 'P';
  dest[3] = 'R';
  dest[4] = 'O';  
  dest[5] = '\0';
  printf("=============\n");
  printf("%s\n", dest);
  printf("%s", str1);
  printf("%s", str2);
  return EXIT_SUCCESS;
}
