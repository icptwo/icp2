// ***
// *** You must modify this file
// ***
#include <stdio.h>  
#include <stdlib.h> 
#include <string.h> 
#include <stdbool.h>
#include "checker.h"
int Levenshtein(const char * str1, const char * str2);

int countWords(char* filename)
{
  FILE * fin = fopen(filename, "r");
  if (fin == NULL)
    { return 0; }
  int count = 0;
  char oneline[MAXLENGTH];
  while (! feof(fin))
    {
      if (fgets(oneline, MAXLENGTH, fin) != NULL)
	{ count ++; }
    }
  fclose(fin);
  return count;
}
bool readWords(char* filename, WordDistance * wd, int numword)
{
  FILE * fin = fopen(filename, "r");
  if (fin == NULL)
    { return false; }
  int count = 0;
  char oneline[MAXLENGTH];
  while (! feof(fin))
    {
      if (fgets(oneline, MAXLENGTH, fin) != NULL)
	{
	  strcpy(wd[count].word, oneline);
	  wd[count].distance = 0;
	  count ++;
	  if (count > numword)
	    {
	      fprintf(stderr, "ERROR, count: %d, numword: %d\n",
		      count, numword);
	    }
	}
    }
  fclose(fin);
  return true;
}
void calculateDistance(WordDistance * wd, int numword, const char * tocheck)
{
  int ind;
  for (ind = 0; ind < numword; ind ++)
    {
      wd[ind].distance = Levenshtein(wd[ind].word, tocheck);
    }
}

static int compareDistance(const void * ptr1, const void * ptr2)
{
  // ptr1 and ptr2 are WordDistance *
  const WordDistance * wd1 = (const WordDistance *) ptr1;
  const WordDistance * wd2 = (const WordDistance *) ptr2; 
  return ((wd1 -> distance) - (wd2 -> distance));
}

void sortDistance(WordDistance * wd, int numword)
{
  qsort(wd, numword, sizeof(WordDistance), compareDistance);
}

void printWord(WordDistance * wd, int numword)
{
  // int shortest = wd[0].distance;
  int ind = 0;
  // while ((ind < numword) && (wd[ind].distance == shortest))
  while (ind < 10)
    {
      printf("%d, %s", wd[ind].distance, wd[ind].word);
      ind ++;
    }
}
