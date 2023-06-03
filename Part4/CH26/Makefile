CFLAGS = -g -Wall -Wshadow 
GCC = gcc $(CFLAGS)
LIBS = -lm
SRCS = main.c bmpfile.c bmpinvert.c bmpcolor.c bmpedge.c
SRCS += bmpequalize.c bmphistogram.c bmpchecker.c bmpmix.c bmpgray.c
TARGET = image
OBJS = $(SRCS:%.c=%.o)
VALGRIND = valgrind --leak-check=full --tool=memcheck --verbose --log-file

$(TARGET): $(OBJS)
	$(GCC) $(OBJS) -o $@ $(LIBS)

.c.o: 
	$(GCC) -c $*.c 

test: $(TARGET)
	rm -f -r outputs/*
	mkdir outputs
	./image inputs/colorchecker.bmp mix outputs/colormix.bmp
	./image inputs/colorchecker.bmp red outputs/checkerred.bmp
	./image inputs/colorchecker.bmp green outputs/checkergreen.bmp
	./image inputs/colorchecker.bmp blue outputs/checkerblue.bmp
	./image inputs/colorchecker.bmp invert outputs/checkinvert.bmp
	./image inputs/building1.bmp checker outputs/b1check.bmp
	./image inputs/building1.bmp invert outputs/b1invert.bmp
	./image inputs/building2.bmp gray outputs/b2gray.bmp
	./image inputs/building2.bmp edge outputs/b2edge.bmp
	./image inputs/dog1.bmp equalize outputs/d1e.bmp
	./image inputs/dog2.bmp equalize outputs/d2e.bmp
	./image inputs/flower1.bmp equalize outputs/f1e.bmp
	./image inputs/flower2.bmp equalize outputs/f2e.bmp
	./image inputs/parade1.bmp red outputs/p1r.bmp
	./image inputs/parade2.bmp blue outputs/p2b.bmp
	./image inputs/pig.bmp green outputs/pigr.bmp

clean:
	rm -f *.o a.out $(TARGET) *log
	rm -f -r outputs *~ 
