// CH08:bubblesort.c
#include <stdio.h>
#include <stdbool.h>
static void swap(int * a, int * b)
{
  int t = * a;
  * a = * b;
  * b = t;
}
void mysort(int * arr, int len)
{
  // find the smallest value and move it to the beginning of the array
  int ind;
  bool sorted = false;
  while (sorted == false)
    {
      sorted = true;
      for (ind = 0; ind < len - 1 ; ind ++) // notice len - 1
	{
	  if (arr[ind] > arr[ind + 1])
	    {
	      swap(& arr[ind], & arr[ind + 1]);
	      sorted = false;
	    }
	}
    }
}
