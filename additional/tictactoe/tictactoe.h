#ifndef TICTACTOE_H
#define TICTACTOE_H
#define NUMSIDE 3
#define NUMCELL (NUMSIDE * NUMSIDE)
#define NUMBOARD 6045 // possible board configuration
// sum (n = 1 to 9, a = ceiling(n / 2)) C(9,n) x C(n, a)
int generateBoard(int numfill);
#endif
