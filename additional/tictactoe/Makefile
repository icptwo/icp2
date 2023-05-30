CFLAGS = -g -Wall -Wshadow
GCC = gcc $(CFLAGS)
# SRCS = testfill.c
SRCS = tictactoe.c main.c
OBJS = $(SRCS:%.c=%.o)
VALGRIND = valgrind --leak-check=full --tool=memcheck --verbose --log-file

tictactoe: $(OBJS) 
	$(GCC) $(OBJS) -o tictactoe
	./tictactoe 

.c.o: 
	$(GCC) $(CFLAGS) -c $*.c 

clean:
	rm -f *.o a.out  log* *~ tictactoe
