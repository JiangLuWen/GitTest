FitFunc: FitFunc.o
	$(CXX) -o $@ $< `root-config --libs` 
	rm -f *.o

FitFunc.o: FitFunc.cxx
	$(CXX) -c -o $@ $< -I`root-config --incdir`
