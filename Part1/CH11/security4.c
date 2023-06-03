// CH11:security4.c
#include <stdio.h>
#include <stdlib.h>
void f0()
{
}
void f1(void) 
{
  char name[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 27};
  name[24] = 0x73; 
  f0();
}
void f2(void) 
{
  printf("f2 has done terrible things\n");
}
int main(int argc, char * * argv) 
{
  f1();	
  return EXIT_SUCCESS;
}
