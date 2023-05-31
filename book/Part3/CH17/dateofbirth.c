// CH17:dateofbirth.c
#include "dateofbirth.h"
#include <stdio.h>
DateOfBirth DateOfBirth_construct(int y, int m, int d)  
{
  DateOfBirth dob;
  dob.year = y;
  dob.month = m;
  dob.date = d;
  return dob;
}
void DateOfBirth_print(DateOfBirth d)
{
  printf("Date of Birth: %d/%d/%d\n", d.year, d.month, d.date);
}
