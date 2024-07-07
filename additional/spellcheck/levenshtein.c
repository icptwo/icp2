#include <string.h>
// algorithm described on
// https://en.wikipedia.org/wiki/Levenshtein_distance
int Levenshtein(const char * str1, const char * str2)
{
  if (strlen(str1) == 0)
    { return strlen(str2); }
  if (strlen(str2) == 0)
    { return strlen(str1); }
  if ((*str1) == (*str2)) // first letter same
    { return Levenshtein(str1 + 1, str2 + 1); }
  return 1 + Levenshtein(str1 + 1, str2 + 1); 
}
