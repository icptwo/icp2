// CH17:person6.h
#ifndef PERSON6_H
#define PERSON6_H
typedef struct
{
  char * name;
  DateOfBirth dob;
} Person;
Person * Person_construct(char * n, int y, int m, int d);
void Person_destruct(Person * p);
Person * Person_copy(Person * p); 
Person * Person_assign(Person * p1, Person * p2);
void Person_print(Person * p);
#endif
