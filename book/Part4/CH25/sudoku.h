// sudoku.h
#ifndef SUDOKU_H
#define SUDOKU_H
#include <stdbool.h>
typedef struct
{
  int filled; // how many cells' values are final
  char cells[9][9]; // cells' values
  bool allowed[9][9][10]; // what is allowed in each cell? [][][0] not used
} Sudoku;
bool readSudoku(char * filename, Sudoku * sud);
void printSudoku(Sudoku * sud);
void saveSudoku(char * filename, Sudoku * sud);
void solveSudoku(Sudoku * sud);
bool networkSudoku(char * ipaddr, int port, Sudoku * sud, int * servsock);
void sendSudoku(int servsock, Sudoku * sud);
#endif
