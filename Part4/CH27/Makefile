# CH27: Makefile
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR) 
VAL = valgrind --tool=memcheck --log-file=vallog --leak-check=full --verbose
SRCS = main.c occur.c compress.c list.c tree.c bits.c # decode.c decode.c
OBJS = $(SRCS:%.c=%.o)

huffman: $(OBJS)
	$(GCC) $(OBJS) -o huffman

test: testgen huffman
	rm -f -r outputs
	mkdir outputs
	for inputpath in inputs/*; do \
	filename=$$(basename $$inputpath); \
	# echo $$name; \
	# echo $$filename; \
	./huffman c $$inputpath outputs/ $$filename; \
	done

testgen: testgen.c
	$(GCC) testgen.c -o testgen
	for num in 1 2 3 4 5 6; do \
	./testgen cases/case$$num inputs/input$$num; \
	done

memory: testhuffman
	$(VAL) ./huffman input2 output2 

.c.o: 
	$(GCC) $(TESTFALGS) -c $*.c 

clean: # remove all machine generated files
	rm -f huffman occur testgen *.o *~ vallog
	rm -f -r inputs/input*
	rm -f -r outputs
