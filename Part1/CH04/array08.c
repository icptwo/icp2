// CH04:array08.c
#include <stdio.h>
#include <stdlib.h>
void incrarr(int * arr, int len)
{
  int ind;
  int * ptr = arr;
  for (ind = 0; ind < len; ind ++)
    {
      (* ptr) ++; 
      ptr ++;
    }
}
void printarr(int * arr, int len)
{
  int ind;
  for (ind = 0; ind < len; ind ++) { printf("%d ", arr[ind]); }
  printf("\n");
}
int main(int argc, char * * argv)
{
  int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
  int arrlen = sizeof(arr) / sizeof(arr[0]);
  printarr(arr, arrlen);
  printf("--------------\n");
  incrarr(& arr[arrlen / 3], arrlen / 2);
  // please notice /3 and /2
  printarr(arr, arrlen);
  return EXIT_SUCCESS;  
}
