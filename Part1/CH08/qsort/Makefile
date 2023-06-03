GCC = gcc
CFLAGS = -g -Wall -Wshadow 

myqsort: main.c compareint.c
	$(GCC) $(CFLAGS) main.c compareint.c -o $@
	./myqsort 20

clean:
	/bin/rm -f input* expected* *.o output* mysort *~


