// ***
// *** DO NOT modify this file
// ***

#ifndef CHECKER_H
#define CHECKER_H
#include <stdio.h>
#include <stdbool.h>
#define MAXLENGTH 41 // the longest word has at most 40 letters
typedef struct
{
  char word[MAXLENGTH]; 
  int distance;
} WordDistance;

int countWords(char* filename);
bool readWords(char* filename, WordDistance * wd, int numword);
void calculateDistance(WordDistance * wd, int numword, const char * tocheck);
void sortDistance(WordDistance * wd, int numword);
void printWord(WordDistance * wd, int numword);
#endif
