# CH24:Makefile
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR) 
SRCS = main.c maze.c
OBJS = $(SRCS:%.c=%.o)

maze: $(OBJS)
	$(GCC) $(OBJS) -o maze

.c.o: 
	$(GCC) $(TESTFALGS) -c $*.c 

test: maze
	for case in 1 2 3; do \
	./maze input$$case > output$$case; \
	diff -w output$$case expected$$case; \
	done

clean: # remove all machine generated files
	rm -f maze *.o output* a.out *~ 



