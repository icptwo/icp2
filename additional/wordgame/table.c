#include "table.h"
#include <stdio.h>
#include <dirent.h>
#include <ctype.h>

static bool readFile(char * filename, int charTable[NUMROW][NUMCOL])
{
  printf("file: %s\n", filename);
  return true;
  FILE * fptr = fopen(filename, "r");
  if (fptr == NULL)
    {
      return false;
    }
  int state = 0;
  char letter;
  int rowindex;
  int colindex;
  while (state != 3)
    {
      if (feof(fptr)) { state = 3; }
      switch (state)
	{
	case 0:
	  letter = fgetc(fptr);
	  if (isalpha(letter)) 
	    {
	      state = 1;
	      rowindex = tolower(letter) - 'a';
	    }	    
	  if (letter == EOF)
	    {
	      state = 3;
	    }
	  break;
	case 1:
	  letter = fgetc(fptr);
	  if (isalpha(letter))
	    {
	      state = 1;
	      colindex = tolower(letter) - 'a';
	      charTable[rowindex][colindex] ++;
	      rowindex = colindex;
	    }
	  else
	    {
	      if (letter == EOF)
		{
		  state = 3;
		}
	      else
		{
		  charTable[rowindex][26] ++;
		  state = 0;
		}
	    }
	  break;
	case 3:
	  break;
	}
    }
  return true;
}

bool buildTable(char * path, int mode, int charTable[NUMROW][NUMCOL])
{
  if (mode == FROMFILE)
    {
      return readFile(path, charTable);
    }
  if (mode == FROMDIR)
    {
      DIR * dir;
      struct dirent *entry;
      dir = opendir(path);
      if (dir == NULL)
	{
	  return false;
	}
      while ((entry = readdir(dir)) != NULL)
	{
	  readFile(entry->d_name, charTable);
	}
      closedir(dir);
    }
  return true;
}

void printTable(int table[NUMROW][NUMCOL])
{
  int row;
  int col;
  for (row = 'a'; row <= 'z'; row ++)
    {
      printf("row = %c:\n", row);
      int rowindex = row - 'a';
      for (col = 'a'; col <= 'z'; col ++)
	{
	  int colindex = col - 'a';
	  printf("   col = %c, value = %d\n", col,
		 table[rowindex][colindex]);
	}
      printf("\n");
    }
}

void completeWord(char * argv3, int charTable[NUMROW][NUMCOL])
{
}
