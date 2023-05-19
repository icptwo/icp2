// CH27:occur.h
// count the number of occurrences of the characters in a file
#ifndef OCCUR_H
#define OCCUR_H
typedef struct
{
  char ascii;     // ASCII value
  int occur;      // how many times does this ASCII value occurs
} CharOccur;
// count the occurrencies of the characters
// return the number of characters 
// return 0 if cannot read from the file
// occur is an array whose elements store the characters
int countOccur(char * filename, CharOccur * occur, int length);
#endif
