#ifndef TICTACTOE_H
#define TICTACTOE_H
#define NUMSIDE 3
#define NUMCELLS (NUMSIDE * NUMSIDE)
struct graphnode;
typedef struct boardnode
{
  struct boardnode * next;
  int cells[NUMCELLS]; // 9 cells, each can store X, O, or ' ' (space)
  // the cells are organized as 0 1 2
  //                            3 4 5
  //                            6 7 8
  struct graphnode * parent;
  struct graphnode * child;
} Board;

typedef struct graphnode
{
  struct graphnode * next;
  Board * brd;
} GraphLink;

void Board_print(Board * brhead);
int Cells_difference(int * cells1, int * cells2, int * change);
int Check_duplicate(int * cells1, int * cells2, int * change);
void Cells_print(int * cells, bool twod);
#endif
