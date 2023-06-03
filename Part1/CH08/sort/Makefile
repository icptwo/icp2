# CH08:sort/Makefile
# build and test mysort function
GCC = gcc
CFLAGS = -g -Wall -Wshadow
VALGRIND = valgrind --tool=memcheck --leak-check=full 
VALGRIND += --verbose --log-file=valog
OBJS = mysort.o main.o
HDRS = mysort.h
test: inputgen mysort 
	   ./mysort 16   < input16   > output16
	   diff output16  expected16
inputgen: 
	  shuf -i 1-1000 -n 16 > input16
	  sort -n input16   > expected16
mysort: $(OBJS) $(HDRS)
	$(GCC) $(CFLAGS) $(OBJS) -o $@
.c.o:
	$(GCC) $(CFLAGS) -c $*.c
memory: inputgen mysort
	$(VALGRIND) ./mysort 16   < input16   > output16
	grep "ERROR" valog
clean:
	/bin/rm -f mysort *.o *~ output16 input16 expected16 valog 
