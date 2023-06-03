# CH05:Makefile1
# This is a comment
# to run it:
# make -f Makefile1
# make test -f Makefile1
# make clean -f Makefile1

GCC = gcc
CFLAGS = -g -Wall -Wshadow
SRCS = aredistinct.c main.c
OBJS = $(SRCS:%.c=%.o) # OBJS = aredistinct.o main.o

program: $(OBJS)
	$(GCC) $(CFLAGS) $(OBJS) -o program # link, no -c

.c.o:
	$(GCC) $(CFLAGS) -c $*.c # compile .c to .o, notice -c

test: program
	for case in 0 1 2 3 4; do \
	echo input$$case; \
	./program inputs/input$$case > output$$case; \
	diff output$$case expected/expected$$case; \
	done

clean:
	/bin/rm -f *.o program *~ *bak output*  