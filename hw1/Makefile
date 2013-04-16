TARGET = hw1
SOURCE = hw1.cxx
CC = g++
LIBS = `root-config --libs`
CFLAGS = `root-config --cflags` -I../include
COMIPLEFLAGS = -fPIC -m -g -Wall -O2

all: $(TARGET)

$(TARGET): hw1.cxx
	$(CC) $(SOURCE) -o $(TARGET) $(LIBS) $(CFLAGS)

clean:
	touch $(TARGET)
	rm $(TARGET)
	rm *~
