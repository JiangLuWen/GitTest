TARGET = hw1
SOURCE = hw1.cxx
CC = g++
LIBS = `root-config --libs`
CFAGS = `root-config --cflags`
all: $(TARGET)

$(TARGET):
	$(CC) $(SOURCE) -o $(TARGET) $(LIBS) $(CFLAGS)

clean:
	rm $(TARGET)
	rm *~
