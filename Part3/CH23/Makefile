# CH23:Makefile
# Makefile for testing rational numbers
GPP = g++ -g
LIBS = -lgtest -pthread
demo: demo.cpp rational.cpp rational.h
	$(GPP) demo.cpp rational.cpp -o demo
	./demo
test: rational_test.cpp rational.cpp rational.h
	$(GPP) rational_test.cpp rational.cpp -o rational_test $(LIBS)
	./rational_test
clean:
	/bin/rm -f *.o a.out rational_test demo
