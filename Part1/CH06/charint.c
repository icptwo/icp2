// CH06:charint.c
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char * * argv)
{
  int v = 55;
  printf("%d\n", v); // C treats integer and character differently
  printf("%c\n", v);
  return EXIT_SUCCESS;
}
