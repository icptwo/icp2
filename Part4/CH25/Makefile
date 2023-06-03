WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR) 
VAL = valgrind --tool=memcheck --log-file=vallog --leak-check=full --verbose
SRCS = main.c sudoku.c
OBJS = $(SRCS:%.c=%.o)

sudoku: $(OBJS)
	$(GCC) $(OBJS) -o sudoku

network: server.c
	$(GCC) server.c -o server

transfer: transferserver.c transferclient.c
	$(GCC) transferclient.c -o transferclient
	$(GCC) transferserver.c -o transferserver

check: check.c
	$(GCC) check.c -o check

.c.o: 
	$(GCC) $(TESTFALGS) -c $*.c 

test: sudoku
	for case in 1 2 3 4 5 6 7 8 9 10 11; do \
	./sudoku f inputs/input$$case output$$case; \
	diff -w output$$case expected/expected$$case; \
	done

memory: sudoku
	$(VAL) ./sudoku f inputs/input2 output2

clean: # remove all machine generated files
	rm -f sudoku *.o output* vallog *~ server client check



