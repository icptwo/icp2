// CH27:binary:compress:occur.h
// count the number of occurrences of the characters in a file
#ifndef OCCUR_H
#define OCCUR_H
typedef struct
{
  char ascii;     // ASCII value
  int occur;
} CharOccur;
// count the occurrencies of the characters
// return the number of characters 
// return 0 if cannot read from the file
// occur is an array whose elements store the characters
int countOccur(char * filename, CharOccur * occur);
void printOccur(CharOccur * occur); // print the array
void sortOccur(CharOccur * occur);  // sort the array
#endif
