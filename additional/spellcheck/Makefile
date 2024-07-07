# ***
# *** You can modify this file. You do not (should not) submit this file
# ***

WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c11 -g $(WARNING) $(ERROR) 
SRCS = main.c checker.c levenshtein.c
OBJS = $(SRCS:%.c=%.o)

main: $(OBJS) 
	$(GCC) $(OBJS) -o main

.c.o: 
	$(GCC) -c $*.c 

test1: main
	./main inputs/list1 billy > output1
	diff output1 expected/expected1

test2: main
	./main inputs/list1 hilly > output2
	diff output2 expected/expected2

test3: main
	./main inputs/list2 purdue > output3
	diff output3 expected/expected3

test4: main
	./main inputs/list2 program > output4
	diff output4 expected/expected4

test5: main
	./main inputs/list4 Lafayette > output5
	diff output5 expected/expected5

clean: # remove all machine generated files
	rm -f main *.o output? *~


