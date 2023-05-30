CFLAGS = -g -Wall -Wshadow
GCC = gcc $(CFLAGS)
# SRCS = testfill.c
SRCS = tictactoe.c
OBJS = $(SRCS:%.c=%.o)
VALGRIND = valgrind --leak-check=full --tool=memcheck --verbose --log-file

testall: code test1 

code: $(OBJS) 
	$(GCC) $(OBJS) -o code

test1: code
	./code 

.c.o: 
	$(GCC) $(CFLAGS) -c $*.c 

clean:
	rm -f *.o a.out code compress? log* *~
