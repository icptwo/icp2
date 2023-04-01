#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>	// socket
#include <arpa/inet.h>	// inet_addr
#include "sudoku.h"
static void initSudoku(Sudoku * sud);
static void removeUsed(Sudoku * sud, int row, int col, char val);
static void printAllow(Sudoku * sud);
static void createSudoku(char * numbers, Sudoku *sud);
static void fillSudoku(Sudoku * sud);
static bool isValidFill(Sudoku * sud, int row, int col, char val);
static bool guessFillHelper(Sudoku * sud, int row, int col);
static void guessFill(Sudoku * sud);
bool fileSudoku(char * filename, Sudoku * sud)
{
  FILE * fptr = fopen(filename, "r");
  if (fptr == NULL) { return false; }
  char numbers[81];
  int cnt = 0;
  for (int row  = 0; row < 9; row ++)
    {
      int ch;
      for (int col = 0; col < 9; col ++)
	{
	  ch = fgetc(fptr);
	  numbers[cnt] = ch;
	  cnt ++;
	}
      ch = fgetc(fptr); // remove '\n'
    }
  fclose(fptr);
  createSudoku(numbers, sud);
  return true;
}
void printSudoku(Sudoku * sud)
{
  if (sud == NULL) { return; }
  printf("   ");
  for (int row = 0; row < 9; row ++) { printf("%c", row + 'A'); }
  printf("\n");
  for (int row = 0; row < 9; row ++)
    {
      printf("%d: ", row + 1);
      for (int col = 0; col < 9; col ++)
	{
	  char val = sud->cells[row][col];
	  if ((val >= '1') && (val <= '9')) { printf("%c", val); }
	  else { printf("-"); } 
	}
      printf("\n");
    }
}
void saveSudoku(char * filename, Sudoku * sud)
{
  FILE * fptr = fopen(filename, "w");
  if (fptr == NULL) { return; }
  for (int row = 0; row < 9; row ++)
    {
      for (int col = 0; col < 9; col ++)
	{ fprintf(fptr, "%c", sud -> cells[row][col]); }
      fprintf(fptr, "\n");
    }
  fclose(fptr);
}
void solveSudoku(Sudoku * sud)
{
  bool progress = true;
  while (progress) // stop if cannot fill any more cell
    {
      int filled = sud -> filled;
      fillSudoku(sud);
      if (filled == (sud -> filled)) { progress = false; } 
    }
  if ((sud -> filled) == 81) { return; } // solved
  printf("need recursion\n");
  printSudoku(sud);
  guessFill(sud);   // need to guess 
}
static void createSudoku(char * numbers, Sudoku *sud)
{
  initSudoku(sud);
  int cnt = 0;
  for (int row = 0; row < 9; row ++)
    {
      for (int col = 0; col < 9; col ++)
	{
	  char ch = numbers[cnt];
	  sud-> cells[row][col] = ch;
	  if ((ch >= '1') && (ch <= '9'))
	    {
	      for (int allow = 1; allow <= 9; allow ++)
		{ sud -> allowed[row][col][allow] = false; }
	      removeUsed(sud, row, col, ch);
	      (sud -> filled) ++;
	    }
	  cnt ++;
	}
    }
  printSudoku(sud);
  printAllow(sud);	  
}
static void initSudoku(Sudoku * sud)
{
  sud -> filled = 0;
  for (int row = 0; row < 9; row ++)
    {
      for (int col = 0; col < 9; col ++)
	{
	  sud -> allowed[row][col][0] = false;
	  for (int allow = 1; allow <= 9; allow ++)
	    { sud -> allowed[row][col][allow] = true; }
	}
    }
}
static void removeUsed(Sudoku * sud, int row, int col, char val)
{
  // remove this value from the row
  for (int colcnt = 0; colcnt < 9; colcnt ++)
    { sud -> allowed[row][colcnt][val - '0'] = false; }
  // remove this value from the column
  for (int rowcnt = 0; rowcnt < 9; rowcnt ++)
    { sud -> allowed[rowcnt][col][val - '0'] = false; }
  // remove this value from the 3 x 3 block
  int rowstart = (row / 3) * 3;
  int colstart = (col / 3) * 3;
  for (int rowcnt = rowstart; rowcnt < rowstart + 3; rowcnt ++)
    {
      for (int colcnt = colstart; colcnt < colstart + 3; colcnt ++)
	{ sud -> allowed[rowcnt][colcnt][val - '0'] = false; } 
    }
}
static void printAllow(Sudoku * sud)
{
  for (int row = 0; row < 9; row ++)
    {
      for (int col = 0; col < 9; col ++)
	{
	  bool skip = true;
	  int allow = 1;
	  while ((allow <= 9) && (skip == true))
	    {
	      if (sud -> allowed[row][col][allow] == true)
		{ skip = false; }
	      allow ++;
	    }
	  if (skip == false)
	    {
	      printf("Allow at [%d][%c]: ", row + 1, col + 'A');
	      for (allow = 1; allow <= 9; allow ++)
		{
		  if (sud -> allowed[row][col][allow] == true)
		    { printf("%d ", allow);	}
		}
	      printf("\n");
	    }
	}
    }
}
static void fillSudoku(Sudoku * sud)
{
  for (int row = 0; row < 9; row ++)
    {
      for (int col = 0; col < 9; col ++)
	{
	  int numallowed = 0;
	  char allowval = '0';
	  for (int allow = 1; allow <= 9; allow ++)
	    {
	      if ((sud -> allowed[row][col][allow]) == true)
		{
		  numallowed ++;
		  allowval = '0' + allow;
		}
	    }
	  if (numallowed == 1)
	    {
	      sud -> cells[row][col] = allowval;
	      (sud -> filled) ++;
	      removeUsed(sud, row, col, allowval);
	    }
	}
    }
}
static void guessFill(Sudoku * sud)
{
  guessFillHelper(sud, 0, 0);
}
static bool guessFillHelper(Sudoku * sud, int row, int col)
{
  bool foundCell = false;
  int findrow = row;
  int findcol = col;
  while ((foundCell == false) && (findrow < 9) && (findcol < 9))
    {
      if ((sud -> cells[findrow][findcol]) == '0') // not assigned
	{ foundCell = true; }
      else
	{
	  findcol ++;
	  if (findcol == 9)
	    {
	      findrow ++;
	      findcol = 0;
	    }
	}
    }
  if (foundCell == false) // all cells filled
    {
      sud -> filled = 81;
      return true;
    } 
  for (int allow = 1; allow <= 9; allow ++)
    {
      if ((sud -> allowed[findrow][findcol][allow]) == true)
	{
	  char val = allow + '0';
	  if (isValidFill(sud, findrow, findcol, val) == true)
	    {
	      sud -> cells[findrow][findcol] = val;
	      if (guessFillHelper(sud, findrow, findcol) == true)
		{ return true; }
	      sud -> cells[findrow][findcol] = '0'; // reset
	    }
	}
    }
  return false;
}
static bool isValidFill(Sudoku * sud, int row, int col, char val)
{
  for (int colcnt = 0; colcnt < 9; colcnt ++)
    {
      if (colcnt != col)
	{
	  if (sud-> cells[row][colcnt] == val) // already used
	    { return false; } 
	}
    }
  for (int rowcnt = 0; rowcnt < 9; rowcnt ++)
    {
      if (rowcnt != row)
	{
	  if (sud -> cells[rowcnt][col] == val)
	    { return false; }
	}
    }
  int rowstart = (row / 3) * 3;
  int colstart = (col / 3) * 3;
  for (int rowcnt = rowstart; rowcnt < rowstart + 3; rowcnt ++)
    {
      for (int colcnt = colstart; colcnt < colstart + 3; colcnt ++)
	{
	  if ((rowcnt != row) && (colcnt != col))
	    {
	      if (sud -> cells[rowcnt][colcnt] == val)
		{ return false; }
	    }
	}
    }
  return true;
}
bool networkSudoku(char * ipaddr, int port, Sudoku * sud, int * servsock)
{
  int sock;
  sock = socket(AF_INET , SOCK_STREAM , 0);
  if (sock == -1) { return false; }
  struct sockaddr_in server;
  server.sin_addr.s_addr = inet_addr(ipaddr);
  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  int rtv = connect(sock , (struct sockaddr *) &server , sizeof(server));
  if (rtv < 0) { return false; }
  char message[1024]; // more than necessary
  int msglen = recv(sock, message, 1024, 0);
  if (msglen != 81) { return false; }
  createSudoku(message, sud);
  * servsock = sock;
  return true;
}
void sendSudoku(int servsock, Sudoku * sud)
{
  char message[1024];
  int cnt = 0;
  for (int row = 0; row < 9; row ++)
    {
      for (int col = 0; col < 9; col ++)
	{
	  message[cnt] = sud -> cells[row][col];
	  cnt ++;
	}
    }
  write(servsock, message, 81);
  int msglen = recv(servsock , message , 1024 , 0);
  if (msglen < 0) { return; }
  message[msglen] = '\0';
  printf("%s\n", message);
  close(servsock);
}
