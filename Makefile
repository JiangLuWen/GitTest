CFLAGS=-g -Wall -fPIC -O2
ello: FitFunc.o
	$(CXX) -o $@ $< $(CFLAGS)
	rm -f *.o

FitFunc.o: FitFunc.cxx
	$(CXX) -c -o $@ $< $(CFLAGS)
