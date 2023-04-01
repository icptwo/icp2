# CH24:Makefile
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR) 
VAL = valgrind --tool=memcheck --log-file=vallog --leak-check=full --verbose
SRCS = main.c maze.c
OBJS = $(SRCS:%.c=%.o)

maze: $(OBJS)
	$(GCC) $(OBJS) -o maze

.c.o: 
	$(GCC) $(TESTFALGS) -c $*.c 

test: maze
	./maze input01 > output01
	diff -w output01 expected01
	./maze input02 > output02
	diff -w output02 expected02

memory: maze
	$(VAL) ./maze input02 > output02

clean: # remove all machine generated files
	rm -f maze *.o output* vallog 



