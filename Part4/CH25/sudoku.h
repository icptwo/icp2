// sudoku.h
#ifndef SUDOKU_H
#define SUDOKU_H
#include <stdbool.h>
typedef struct
{
  int filled;
  char cells[9][9];
  bool allowed[9][9][10]; // [][][0] not used
} Sudoku;
bool fileSudoku(char * filename, Sudoku * sud);
void printSudoku(Sudoku * sud);
void saveSudoku(char * filename, Sudoku * sud);
void solveSudoku(Sudoku * sud);
bool networkSudoku(char * ipaddr, int port, Sudoku * sud, int * servsock);
void sendSudoku(int servsock, Sudoku * sud);
#endif
