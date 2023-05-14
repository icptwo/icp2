// CH25:check.c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int compareChar(const void * arg1, const void * arg2)
{
  char * ptr1 = (char *) arg1;
  char * ptr2 = (char *) arg2;
  return ((* ptr1) - (* ptr2));
}
bool check9cells(char * cells)
{
  // each number between 1 to 9 should appear exactly once
  qsort(cells, 9, sizeof(char), compareChar);
  for (int val = 0; val < 9; val ++)
    {
      if (cells[val] != (val + 1 + '0')) { return false; }
    }
  return true;
}
bool checkSudoku(char * filename)
{
  FILE * fptr = fopen(filename, "r");
  if (fptr == NULL) { return false; }
  char sudoku[9][9];
  int row, col, ch;
  // read the input file
  for (row = 0; row < 9; row ++)
    {
      for (col = 0; col < 9; col ++)
	{
	  ch = fgetc(fptr);
	  if ((ch >= '0') && (ch <= '9'))
	    { sudoku[row][col] = ch; }
	  else { return false; }
	}
      ch = fgetc(fptr);
      if ((ch != '\n') && (ch != EOF)) { return false; }
    }
  char cells[9];
  // check columns
  for (row = 0; row < 9; row ++)
    {
      for (col = 0; col < 9; col ++)
	{ cells[col] = sudoku[row][col]; }
      if (check9cells(cells) == false) { return false; }
    }
  // check rows
  for (col = 0; col < 9; col ++)
    {
      for (row = 0; row < 9; row ++)
	{ cells[row] = sudoku[row][col]; }
      if (check9cells(cells) == false) { return false; }
    }
  // check blocks
  for (int blrow = 0; blrow < 7; blrow += 3)
    {
      for (int blcol = 0; blcol < 7; blcol += 3)
	{
	  int cnt = 0;
	  for (row = 0; row < 3; row ++)
	    {
	      for (col = 0; col < 3; col ++)
		{
		  cells[cnt] = sudoku[blrow + row][blcol + col];
		  cnt ++;
		}
	    }
	  if (check9cells(cells) == false) { return false; }
	}      
    }
  return true;
}
int main(int argc, char ** argv)
{
  if (argc != 2) { return EXIT_FAILURE; }
  if (checkSudoku(argv[1]) == false)
    { printf("invalid\n"); }
  else { printf("valid\n"); }
  return EXIT_SUCCESS;
}
