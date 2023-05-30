#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tictactoe.h"
void Board_print(Board * brhead)
{
  Board * br;
  while (brhead != NULL)
    {
      br = brhead -> next;
      Cells_print(brhead -> cells, true);
      brhead = br;
    }
}
/*
int Cells_equivalent(int * cells1, int * cells2)
{
  int ind;
  for (ind = 0; ind < NUMCELLS; ind ++)
    {
      if (cells1[ind] != cells2[ind]) { return false; }
    }
  return true;
}
*/
void Cells_rotate(int * src, int * dest) // clockwise
{
  // This is how rotate works
  // original  new
  // 0 1 2     6 3 0
  // 3 4 5     7 4 1
  // 6 7 8     8 5 2
  int transition[NUMCELLS] =
    {6, 3, 0,
     7, 4, 1,
     8, 5, 2};
  int ind;
  for (ind = 0; ind < NUMCELLS; ind ++)
    { dest[ind] = src[transition[ind]]; }
  /*
  printf("Cells_rotate\n");
  printf("source\n");
  Cells_print(src, true);
  printf("destination\n");
  Cells_print(dest, true);
  */
}

void Cells_Hmirror(int * src, int * dest)
{
  // This is how horizontal mirror works
  // original  new
  // 0 1 2     6 7 8
  // 3 4 5     3 4 5
  // 6 7 8     0 1 2
  int transition[NUMCELLS] =
    {6, 7, 8,
     3, 4, 5,
     0, 1, 2};
  int ind;
  for (ind = 0; ind < NUMCELLS; ind ++)
    { dest[ind] = src[transition[ind]]; }
}

void Cells_Vmirror(int * src, int * dest)
{
  // This is how vertical mirror works
  // original  new
  // 0 1 2     2 1 0
  // 3 4 5     5 4 3
  // 6 7 8     8 7 6
  int transition[NUMCELLS] =
    {2, 1, 0,
     5, 4, 3,
     8, 7, 6};
  int ind;
  for (ind = 0; ind < NUMCELLS; ind ++)
    { dest[ind] = src[transition[ind]]; }
}

void Cells_copy(int * src, int * dest)
{
  int ind;
  for (ind = 0; ind < NUMCELLS; ind ++)
    { dest[ind] = src[ind]; }
}

int Check_duplicate(int * cells1, int * cells2, int * change)
// return true if br1 is equivalent to br2
// two boards are equivalent if
// (1) they point to the same object
// (2) they have the same symbols in the same cells
// (3) they are equivalent by rotation or mirror (or both)
{
  // printf("run Check_duplicate\n");
  if (cells1 == cells2) { return 0; }
  /* 
  printf("cells1:\n");
  Cells_print(cells1, true);
  printf("cells2:\n");
  Cells_print(cells2, true);
  */
  int maxsum = NUMCELLS;
  int sum;
  if (Cells_difference(cells1, cells2, change) == 0)
    { return true; }
  int srccells[NUMCELLS];
  int destcells[NUMCELLS];
  Cells_copy(cells1, srccells);
  int ind;
  for (ind = 0; ind < 3; ind ++) // rotate at most 3 times
    {
      Cells_rotate(srccells, destcells);
      sum = Cells_difference(destcells, cells2, change);
      if (sum == 0) { return 0; }
      if (maxsum > sum) { maxsum = sum; }
      Cells_copy(destcells, srccells);
    }
  Cells_copy(cells1, srccells);
  Cells_Vmirror(srccells, destcells);
  for (ind = 0; ind < 4; ind ++) 
    {
      sum = Cells_difference(destcells, cells2, change);
      if (sum == 0) { return 0; }
      if (maxsum > sum) { maxsum = sum; }
      Cells_copy(destcells, srccells);
      Cells_rotate(srccells, destcells);
    }
  Cells_copy(cells1, srccells);
  Cells_Hmirror(srccells, destcells);
  for (ind = 0; ind < 4; ind ++) 
    {
      sum = Cells_difference(destcells, cells2, change);
      if (sum == 0) { return 0; }
      if (maxsum > sum) { maxsum = sum; }
      Cells_copy(destcells, srccells);
      Cells_rotate(srccells, destcells);
    }
  return maxsum;
}

void Cells_print(int * cells, bool twod)
{
  if (twod == false)
    {
      int ind;
      for (ind = 0; ind < NUMCELLS; ind ++)
	{ printf("%c ", cells[ind]); }
      printf("\n\n");
      return;
    }
  int indr;
  int indc;
  for (indr = 0; indr < NUMSIDE; indr ++)
    {
      for (indc = 0; indc < NUMSIDE; indc ++)
	{
	  { printf("%c ", cells[indr * NUMSIDE + indc]); }
	}
      printf("\n");
    }
  printf("\n");
}

Board * Board_append(int * cells, Board * brhead)
{
  Board * br = brhead;
  /*
  printf("consider to append\n");
  Cells_print(cells, true);
  */
  int change;
  while (br != NULL)
    {
      if (Check_duplicate(cells, br -> cells, & change) == 0)
	{ return brhead; }
      br = br -> next;
    }
  // printf("it is appended\n\n");
  br = malloc(sizeof(Board));
  br -> next = brhead;
  br -> parent = NULL;
  br -> child = NULL;
  Cells_copy(cells, br -> cells);
  return br;
}
		  
void Cells_fill(int * cells, int numX, int numO, int ind, Board ** brhead)
// how many more X or O need to fill?
// the largest index already used for X or O?
{
  if ((numX == 0) && (numO == 0))
    {
      // successful
      // Cells_print(cells, false);
      * brhead = Board_append(cells, * brhead);
      return;
    } 
  if (numX > (NUMCELLS - ind))
    { return; } // do not have enough cells to fill X
  if (numO > (NUMCELLS - ind))
    { return; } // do not have enough cells to fill O
  // fill X
  if (numX > 0)
    {
      cells[ind] = 'X';
      Cells_fill(cells, numX - 1, numO, ind + 1, brhead);
      cells[ind] = '-'; // unfill the cell
    }
  // fill O
  if (numO > 0)
    {
      cells[ind] = 'O';
      Cells_fill(cells, numX, numO - 1, ind + 1, brhead);
      cells[ind] = '-'; // unfill the cell
    }  
  Cells_fill(cells, numX, numO, ind + 1, brhead);
}

typedef struct
{
  Board * tttboard[NUMCELLS + 1];
  // index = how many cells filled, [0] not used
  // if index = 2n, n X and n O
  // if index = 2n + 1, (n + 1) X and n O
} Graph;

void Board_add(int numfill, Board * * brhead)
{
  int cells[NUMCELLS];
  int ind;
  for (ind = 0; ind < NUMCELLS; ind ++)
    { cells[ind] = '-'; }
  int numO = numfill / 2;
  int numX = numfill - numO;
  Cells_fill(cells, numX, numO, 0, brhead);
}

int Cells_difference(int * cells1, int * cells2, int * change)
{
  /*
  printf("Cells_difference\n");
  printf("cells1\n");
  Cells_print(cells1, true);
  printf("cells2\n");
  Cells_print(cells2, true);
  */
  int sum = 0;
  int ind;
  for (ind = 0; ind < NUMCELLS; ind ++)
    {
      if (cells1[ind] != cells2[ind])
	{
	  sum ++;
	  * change = cells2[ind];
	} 
    }
  return sum;
}

void Graph_addEdge(Graph * brgh)
{
  Board * br1;
  Board * br2;
  int numfill;
  for (numfill = 1; numfill < NUMCELLS; numfill ++)
    {
      br1 = brgh -> tttboard[numfill];
      while (br1 != NULL)
	{
	  br2 = brgh -> tttboard[numfill + 1];
	  while (br2 != NULL)
	    {
	      int change;
	      int diff = Check_duplicate(br1 -> cells, br2 -> cells, & change);
	      bool addlink = false;
	      if (diff == 1)
		{
		  /*
		  if ((numfill % 2) && (change == 'X'))
		    { addlink = true; }
		  if (((numfill % 2) == 1) && (change == 'O'))
		    { addlink = true; }
		  */
		  addlink = true;
		}
	      if (addlink == true)
		{
		  /*
		  printf("parent\n");
		  Cells_print(br1 -> cells, false);
		  printf("child\n");
		  Cells_print(br2 -> cells, false);
		  */
		  GraphLink * parent = malloc(sizeof(GraphLink));
		  parent -> next = br2 -> parent;
		  parent -> brd = br1;
		  br2 -> parent = parent;
		  GraphLink * child = malloc(sizeof(GraphLink));
		  child -> next = br1 -> child;
		  child -> brd = br2;
		  br1 -> child = child;
		}
	      br2 = br2 -> next;
	    }	  
	  br1 = br1 -> next;
	}
    }  
}
