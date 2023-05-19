# CH27: Makefile
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR) 
VAL = valgrind --tool=memcheck --log-file=vallog --leak-check=full --verbose
SRCS = main.c # compress.c list.c tree.c occur.c bits.c main.c decode.c decode.c
OBJS = $(SRCS:%.c=%.o)

huffman: $(OBJS)
	$(GCC) $(OBJS) -o huffman

test: huffman
	for name in inputs/input*; do \
	echo $$name; \
	filename=$$(basename $$name); \
	echo $$filename; \
	./huffman c inputs/ $$filename outputs/; \
	done
	# ./huffman input1 output1 
	# ./huffman input2 output2 

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
