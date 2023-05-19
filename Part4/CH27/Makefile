# CH27: Makefile
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR) 
VAL = valgrind --tool=memcheck --log-file=vallog --leak-check=full --verbose
SRCS = compress.c list.c tree.c occur.c bits.c main.c decode.c decode.c
OBJS = $(SRCS:%.c=%.o)

huffman: $(OBJS)
	$(GCC) $(OBJS) -o huffman
	./huffman input1 output1 
	./huffman input2 output2 
	./huffman input3 output3
	./huffman input4 output4 

convert: convert.c
	$(GCC) convert.c -o convert
	for num in 1 2 3 4 5 6; do \
	./convert inputs/case$$num inputs/input$$num; \
	done

memory: testhuffman
	$(VAL) ./huffman input2 output2 

.c.o: 
	$(GCC) $(TESTFALGS) -c $*.c 

clean: # remove all machine generated files
	rm -f huffman occur convert *.o *~ vallog
	rm -f -r inputs/input*
	rm -f -r outputs
