// CH16:combine.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void printArray(int * arr, int length)
{
  int ind;
  for (ind = 0; ind < length; ind ++)
    {
      if (arr[ind] == 1)
	{ printf("%c ", ind + 'A'); }
    }
  printf("\n");
}
// arr: array storing whether an element is selected or not
// ind: index of the item being decided on whether it is selected
// num: the total number of items
// toselect: the number of items to be selected
// selected: the number of items already selected
void combineHelp(int * arr, int ind, int num, int toselect, int selected)
{
  if (selected == toselect) // select enough items
    {
      printArray(arr, num);
      return;
     }
  if (ind == num) // end of array, no more item to select
    { return; } 
  // select this element
  arr[ind] = 1; 
  combineHelp(arr, ind + 1, num, toselect, selected + 1); 
  // do not select this element
  arr[ind] = 0; 
  combineHelp(arr, ind + 1, num, toselect, selected);
}
void combine(int * arr, int len, int toselect)
{
  combineHelp(arr, 0, len, toselect, 0);
}
int main(int argc, char * argv[])
{
  if (argc != 3)
    { return EXIT_FAILURE; } // need two numbers
  int num = (int) strtol(argv[1], NULL, 10);
  if (num <= 0)
    { return EXIT_FAILURE; }
  int toselect = (int) strtol(argv[2], NULL, 10);
  if ((toselect <= 0) || (toselect > num))
    { return EXIT_FAILURE; }
  int * arr;
  arr = malloc(sizeof(int) * num);
  int ind;
  for (ind = 0; ind < num; ind ++)
    { arr[ind] = 0; }
  combine(arr, num, toselect);
  free (arr);
  return EXIT_SUCCESS;
}
