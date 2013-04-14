ello: FitFunc.o
	$(CXX) -o $@ $<
	rm -f *.o

FitFunc.o: FitFunc.cxx
	$(CXX) -c -o $@ $<
