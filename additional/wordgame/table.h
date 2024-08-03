#ifndef TABLE_H
#define TABLE_H
#include <stdbool.h>
enum {FROMDIR, FROMFILE};
#define NUMROW 26
#define NUMCOL 28
bool buildTable(char * path, int mode, int charTable[NUMROW][NUMCOL]);
void printTable(int charTable[NUMROW][NUMCOL]);
void completeWord(char * argv3, int charTable[NUMROW][NUMCOL]);
#endif
