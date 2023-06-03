// CH22:outsync.c
// multiple threads read and modify a shared variable
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUMBER_THREAD 16
void * threadfunc(void *intarg)
{
  int * intptr = (int *) intarg;
  while (1)
    {
      (* intptr) ++;
      (* intptr) --;
      if ((* intptr) != 0)
	{
	  printf("value is %d\n", * intptr);
	  return NULL;
	}
    }
  return NULL;
}
int main (int argc, char *argv[])
{
  pthread_t tid[NUMBER_THREAD];
  int rtv; // return value of pthread_create
  int ind;
  int intarg = 0;
  for (ind = 0; ind < NUMBER_THREAD; ind ++)
    {
      rtv = pthread_create(& tid[ind], NULL, threadfunc, (void *) & intarg);
      if (rtv != 0)
	{
	  printf("pthread_create() fail %d\n", rtv);
	  return EXIT_FAILURE;
	}
    }
  for (ind = 0; ind < NUMBER_THREAD; ind ++)
    {
      rtv = pthread_join(tid[ind], NULL);
      if (rtv != 0)
	{
	  printf("pthread_join() fail %d\n", rtv);
	  return EXIT_FAILURE;
	}
    }
  return EXIT_SUCCESS;
}
