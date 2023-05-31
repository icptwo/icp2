// CH22:threaddata.h
#ifndef THREADDATA_H
#define THREADDATA_H
typedef struct
{
  unsigned int minval; // specify the elements to check
  unsigned int maxval;
  int numSol;          // number of solutions
  int * setA;          // shared array, not changed by threads
  int sizeA;
  int kval;
} ThreadData;
#endif
