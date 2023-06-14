# CH22:Makefile
SHELL = /bin/bash
GCC = gcc
CFLAGS = -g -Wall -Wshadow
LIBS = -lpthread
OBJS = countint.o isvalid.o subsetequal.o main.o

thread: thread.c
	$(GCC) $(CFLAGS) thread.c -o thread $(LIBS)
	./run-valgrind.sh ./thread

sequential: sequential.c $(OBJS)
	$(GCC) $(CFLAGS) sequential.c $(OBJS) -o sequential

parallel: parallel.c $(OBJS)
	$(GCC) $(CFLAGS) parallel.c $(OBJS) -o parallel $(LIBS)

sync: sync.c
	$(GCC) $(CFLAGS) sync.c -o sync $(LIBS)
	./sync

outsync: outsync.c
	$(GCC) $(CFLAGS) outsync.c -o outsync $(LIBS)
	./outsync

testall: parallel sequential testgen
	/bin/rm -f -r outputs
	mkdir outputs
	# go through all test cases stored in inputs/
	for case in inputs/*; do \
		# echo $$case; \
		# dirname $$case; \
		filename=$$(basename $$case); \
		# echo $$filename; \
		./parallel $$case | sort > outputs/$$filename.p; \
		./sequential $$case | sort > outputs/$$filename.s; \
		diff outputs/$$filename.p outputs/$$filename.s; \
	done

testgen: testgen.c
	$(GCC) $(CFLAGS) testgen.c -o testgen
	/bin/rm -f -r inputs
	mkdir inputs
	# 1 1: valid input, subset sum: yes
	# 1 0: valid input, subset sum: no
	# 0 0: invalid input
	for case in 5 10 15 20 ; do \
	./testgen  $$case 1 1 > inputs/validyes$$case; \
	./testgen  $$case 1 0 > inputs/validno$$case; \
	./testgen  $$case 0 0 > inputs/invalid$$case; \
	done

.c.o: 
	$(GCC) $(CFLAGS) -c $*.c 

clean:
	/bin/rm -f thread seqout* parallel  
	/bin/rm -f sequential log* testgen *.o
	/bin/rm -f -r outputs sync outsync inputs
