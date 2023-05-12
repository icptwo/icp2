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

testinputs: parallel sequential testgen
	/bin/rm -f -r outputs
	mkdir outputs
	for case in inputs/*; do \
		echo $$case; \
		dirname $$case; \
		filename=$$(basename $$case); \
		echo $$filename; \
		./parallel $$case > outputs/$$filename.result; \
	done

testall: parallel sequential
	/bin/rm -f -r outputs # remove the directory
	mkdir outputs # create the directory
	for case in 1 2 3 4 5; do \
	echo input$$case; \
	./parallel inputs/validyes$$case > outputs/pa_out_vy$$case; \
	./parallel inputs/validno$$case > outputs/pa_out_vn$$case; \
	./parallel inputs/invalid$$case > outputs/pa_out_iv$$case; \
	./sequential inputs/validyes$$case > outputs/se_out_vy$$case; \
	./sequential inputs/validno$$case > outputs/se_out_vn$$case; \
	./sequential inputs/invalid$$case > outputs/se_out_iv$$case; \
	done

oldtestall: parallel sequential
	./parallel inputs/validyes1 > outputs/paloutvy1
	./parallel inputs/validyes2 > outputs/paloutvy2
	./parallel inputs/validyes3 > outputs/paloutvy3
	./parallel inputs/validyes4 > outputs/paloutvy4
	./parallel inputs/validyes5 > outputs/paloutvy5
	# ./parallel inputs/validyes6 > outputs/paloutvy6 # this will tkae long time
	./parallel inputs/validno1  > outputs/paloutvn1
	./parallel inputs/validno2  > outputs/paloutvn2
	./parallel inputs/validno3  > outputs/paloutvn3
	./parallel inputs/validno4  > outputs/paloutvn4
	./parallel inputs/validno5  > outputs/paloutvn5
	# ./parallel inputs/validno6  > outputs/paloutvn6
	./parallel inputs/invalid1  > outputs/paloutiv1
	./parallel inputs/invalid2  > outputs/paloutiv2
	./parallel inputs/invalid3  > outputs/paloutiv3
	./parallel inputs/invalid4  > outputs/paloutiv4
	./parallel inputs/invalid5  > outputs/paloutiv5
	# ./parallel inputs/invalid6  > outputs/paloutiv6
	./sequential inputs/validyes1 > outputs/seqoutvy1
	./sequential inputs/validyes2 > outputs/seqoutvy2
	./sequential inputs/validyes3 > outputs/seqoutvy3
	./sequential inputs/validyes4 > outputs/seqoutvy4
	./sequential inputs/validyes5 > outputs/seqoutvy5
	# ./sequential inputs/validyes6 > outputs/seqoutvy6
	./sequential inputs/validno1  > outputs/seqoutvn1
	./sequential inputs/validno2  > outputs/seqoutvn2
	./sequential inputs/validno3  > outputs/seqoutvn3
	./sequential inputs/validno4  > outputs/seqoutvn4
	./sequential inputs/validno5  > outputs/seqoutvn5
	# ./sequential inputs/validno6  > outputs/seqoutvn6
	./sequential inputs/invalid1  > outputs/seqoutiv1
	./sequential inputs/invalid2  > outputs/seqoutiv2
	./sequential inputs/invalid3  > outputs/seqoutiv3
	./sequential inputs/invalid4  > outputs/seqoutiv4
	./sequential inputs/invalid5  > outputs/seqoutiv5
	# ./sequential inputs/invalid6  > outputs/seqoutiv6

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
	./testgen  $$case  0 0 > inputs/invalid$$case; \
	done

.c.o: 
	$(GCC) $(CFLAGS) -c $*.c 

clean:
	/bin/rm -f thread seqout* parallel  
	/bin/rm -f sequential log* testgen *.o
	/bin/rm -f -r outputs sync outsync inputs
