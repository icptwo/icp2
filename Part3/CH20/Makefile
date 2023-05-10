# CH20:Makefile
GCC = gcc
CFLAGS = -g -Wall -Wshadow
LIBS =
SOURCES = sparse.c sparsemain.c
TARGET = main
VALGRIND = valgrind --tool=memcheck --verbose --log-file
TEST0 = inputs/input0A inputs/input0B output0
TEST1 = inputs/input1A inputs/input1B output1

sparsemain: $(SOURCES)
	$(GCC) $(CFLAGS) $(SOURCES) -o $@
	./sparsemain $(TEST0)
	diff -w output0 expected/expected0
	./sparsemain $(TEST1)
	diff -w output1 expected/expected1
	$(VALGRIND)=valgrindlog0 ./sparsemain $(TEST0)
	$(VALGRIND)=valgrindlog1 ./sparsemain $(TEST1)
	grep "ERROR SUMMARY" valgrindlog*

clean:
	/bin/rm -f sparsemain *~ outputs/* *log*
