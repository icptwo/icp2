# CH09:Makefile
# build and test addint.c
GCC = gcc
CFLAGS = -g -Wall -Wshadow
addint: addint.c
	$(GCC) $(CFLAGS) addint.c -o addint
	./addint input1 input2 output
	diff output expected
clean:
	/bin/rm -f addint *.o *~ output
