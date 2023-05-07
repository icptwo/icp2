// CH17:person.h
#ifndef PERSON_H
#define PERSON_H
typedef struct
{
  // date of birth
  int year;
  int month;
  int date;
  char * name; // this is a pointer
} Person;
Person * Person_construct(int y, int m, int d, char * n);
void Person_destruct(Person * p);
void Person_print(Person * p);
#endif
