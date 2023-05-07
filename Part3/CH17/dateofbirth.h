// CH17:dateofbirth.h
#ifndef DATEOFBIRTH_H
#define DATEOFBIRTH_H
typedef struct
{
  int year;
  int month;
  int date;
} DateOfBirth;
DateOfBirth DateOfBirth_construct(int y, int m, int d);
void DateOfBirth_print(DateOfBirth d);
#endif
