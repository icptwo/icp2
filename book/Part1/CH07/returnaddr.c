// CH07:returnaddr.c
#include <stdio.h>
#include <stdlib.h>
int * f1(void)
{
  int val;
  return & val;
}
int main(int argc, char * * argv)
{
  int * ptr = f1();
  * ptr = 10;
  return EXIT_SUCCESS;
}
