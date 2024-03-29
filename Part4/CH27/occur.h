// CH27:occur.h
// count the number of occurrences of the characters in a file
#ifndef OCCUR_H
#define OCCUR_H
#include <stdio.h>
#define NUMCHAR 256
typedef struct
{
  unsigned char ascii; // ASCII value
  int occur; // how many times does this ASCII value occurs
} CharOccur;
// count the occurrencies of the characters
// return the total number of characters in the file
// return 0 if cannot read from the file
// occur is an array whose elements store the characters and occurrences
int countOccur(char * filename, CharOccur * occur, int length);
void printOccur(CharOccur * occur, int length, FILE * pfptr);
int compareOccur(const void * p1, const void * p2);
#endif
