# CH18:Makefile
GCC = gcc
CFLAGS = -g -Wall -Wshadow 
VALGRIND = valgrind --tool=memcheck --verbose --log-file=valog
SRCS = listdelete.c   listinsert.c  listprint.c
SRCS += listdestroy.c  listmain.c    listsearch.c
OBJS = $(SRCS:%.c=%.o) # OBJS = aredistinct.o main.o

list: $(OBJS)
	$(GCC) $(CFLAGS) $(OBJS) -o $@
	./list
	$(VALGRIND) ./list
	grep "ERROR SUMMARY" valog

.c.o:
	$(GCC) $(CFLAGS) -c $*.c 

clean:
	/bin/rm -f *.o list valog
