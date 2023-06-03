# CH21:build/Makefile
# build a binary tree from in-order and post-order
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR) 
VAL = valgrind --tool=memcheck --log-file=vallog
VAL += --leak-check=full --verbose

SRCS = main.c tree.c
OBJS = $(SRCS:%.c=%.o)

build: testgen $(OBJS)
	$(GCC) $(OBJS) -o build
	./build inorder postorder output1
	diff -w output1 preorder

testgen: testgen.o tree.o
	$(GCC) testgen.o tree.o -o testgen
	./testgen 18 inorder postorder preorder 6 

.c.o: 
	$(GCC) $(TESTFALGS) -c $*.c 

memory: build
	$(VAL) ./build  inorder postorder output1

clean: # remove all machine generated files
	rm -f build *.o output? vallog testgen inorder postorder preorder *~
