# CH27: Makefile
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR) 
VAL = valgrind --tool=memcheck --log-file=vlog --leak-check=full --verbose
SRCS = main.c occur.c compress.c list.c tree.c bits.c decompress.c
OBJS = $(SRCS:%.c=%.o)

huffman: $(OBJS)
	$(GCC) $(OBJS) -o huffman

compress: testgen huffman
	rm -f -r compressed
	mkdir compressed
	for origpath in original/*; do \
	filename=$$(basename $$origpath); \
	./huffman c $$origpath compressed/ $$filename; \
	done

decompress: compress
	rm -f -r restored
	mkdir restored
	for comppath in compressed/*cmp; do \
	filename=$$(basename $$comppath); \
	echo $$filename; \
	./huffman d $$comppath restored/ $$filename; \
	done
	# compare the original with the decompressed files
	for origpath in original/*; do \
	filename=$$(basename $$origpath); \
	echo $$filename; \
	diff $$origpath restored/$$filename.cmp.res; \
	done

testgen: testgen.c
	$(GCC) testgen.c -o testgen
	for num in 1 2 3 4 5 6 7 8; do \
	./testgen cases/case$$num original/input$$num; \
	done

memory1: huffman
	$(VAL) ./huffman c original/King1963 compressed/ King1963

memory2: huffman
	$(VAL) ./huffman d compressed/King1963.cmp restored/ King1963.cmp

.c.o: 
	$(GCC) $(TESTFALGS) -c $*.c 

clean: # remove all machine generated files
	rm -f huffman occur testgen *.o *~ vallog
	rm -f -r original/input*
	rm -f -r compressed restored vlog
