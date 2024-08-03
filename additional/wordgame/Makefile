# ***
# *** DO NOT modify this file 
# ***

WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR) 

SRCS = main.c table.c
OBJS = $(SRCS:%.c=%.o)

# diff -w means do not care about space

main: $(OBJS) 
	$(GCC) $(TESTFALGS) $(OBJS) -o main

.c.o: 
	$(GCC) $(TESTFALGS) -c $*.c 

testall: test1 test2 test3 test4 test5 test6

test1: main
	./main inputs/input1 "on" > output1
	diff -w output1 expected/expected1

test2: main
	./main inputs/input2 "t" > output2
	diff -w output2 expected/expected2

test3: main
	./main inputs/input3 "ly" > output3
	diff -w output3 expected/expected3

test4: main
	./main inputs/input4 "ss" > output4
	diff -w output4 expected/expected4

test5: main
	./main inputs/input5 "the" > output5
	diff -w output5 expected/expected5

test6: main
	./main inputs/input6 "aa" > output6
	diff -w output6 expected/expected6


clean: # remove all machine generated files
	rm -f main *.o output* *~



