WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR) 
VAL = valgrind --tool=memcheck --log-file=vallog --leak-check=full --verbose
SRCS = decompress.c list.c tree.c
OBJS = $(SRCS:%.c=%.o)

decompress: $(OBJS)
	$(GCC) $(OBJS) -o decompress
	./decompress input1 output1 
	./decompress input2 output2 

.c.o: 
	$(GCC) $(TESTFALGS) -c $*.c 

memory: decompress
	$(VAL) ./decompress input2 output2 

clean: # remove all machine generated files
	rm -f decompress output? *.o *~ vallog
