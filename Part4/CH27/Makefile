# CH27: Makefile
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR) 
VAL = valgrind --tool=memcheck --log-file=vallog --leak-check=full --verbose
SRCS = main.c occur.c compress.c list.c tree.c bits.c decompress.c
OBJS = $(SRCS:%.c=%.o)

huffman: $(OBJS)
	$(GCC) $(OBJS) -o huffman

compress: testgen huffman
	rm -f -r compressed
	mkdir compressed
	for origpath in original/*; do \
	filename=$$(basename $$origpath); \
	# echo $$name; \
	# echo $$filename; \
	./huffman c $$origpath compressed/ $$filename; \
	done

decompress: huffman
	rm -f -r decompressed
	mkdir decompressed
	for comppath in compressed/*out; do \
	filename=$$(basename $$comppath); \
	echo $$filename; \
	./huffman d $$comppath decompressed/ $$filename; \
	done

testgen: testgen.c
	$(GCC) testgen.c -o testgen
	for num in 1 2 3 4 5 6; do \
	./testgen cases/case$$num original/original$$num; \
	done

memory: testhuffman
	$(VAL) ./huffman input2 output2 

.c.o: 
	$(GCC) $(TESTFALGS) -c $*.c 

clean: # remove all machine generated files
	rm -f huffman occur testgen *.o *~ vallog
	rm -f -r original/original*
	rm -f -r compressed decompressed
