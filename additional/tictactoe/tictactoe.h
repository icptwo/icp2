#ifndef TICTACTOE_H
#define TICTACTOE_H
#define NUMSIDE 3
#define NUMCELL (NUMSIDE * NUMSIDE)
typedef struct
{
  int cells[NUMCELL];
} Board;
void initBoard(Board * oneboard);
void printBoard(Board * oneboard, int dim);
int generateBoard(Board * allboard, int choice);
#endif
