# CH27:binary:compress:Makefile
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR) 
VAL = valgrind --tool=memcheck --log-file=vallog --leak-check=full --verbose
SRCS = compress.c list.c tree.c occur.c bits.c
OBJS = $(SRCS:%.c=%.o)

compress: $(OBJS)
	$(GCC) $(OBJS) -o compress
	./compress input1 output1 
	./compress input2 output2 
	./compress input3 output3
	./compress input4 output4 

.c.o: 
	$(GCC) $(TESTFALGS) -c $*.c 

memory: compress
	$(VAL) ./compress input2 output2 

clean: # remove all machine generated files
	rm -f compress occur convert *.o *~ vallog
