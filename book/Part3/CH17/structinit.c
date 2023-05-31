// CH17:structinit.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma pack(1) // tell compiler not to pad any space
// assume
// sizeof(char) = 1,   sizeof(int) = 4, 
// sizeof(double) = 8, sizeof(a pointer) = 8
typedef struct
{
  int a;
  int b;
  int c;
  int d;
} Counter;
int func(Counter * cnt, int n)
{
  (cnt -> a) ++;
  if (n == 0)
    {
      (cnt -> b) ++;
      return 1;
    }
  if (n == 1)
    {
      (cnt -> c) ++;
      return 2;
    }
  int x = func(cnt, n - 1);
  int y = func(cnt, n - 2);
  (cnt -> d) ++;
  return (x + y);
}
int main(int argc, char ** argv)
{
  Counter cnt =
    {
     .a = 0, // same as cnt.a = 0
     .b = 0, // same as cnt.b = 0
     .c = 0,
     .d = 0
    };
  int v = func(& cnt, 5);
  printf("cnt = (%d, %d, %d, %d)\n", cnt.a, cnt.b, cnt.c, cnt.d);
  printf("v = %d\n", v);
  return EXIT_SUCCESS;
}
