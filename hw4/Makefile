TARGET = hw4
SOURCE = $(TARGET).cxx
CC = g++
LIBS = `root-config --libs`
CFLAGS = `root-config --cflags` -I../include
COMIPLEFLAGS = -fPIC -g -Wall -O2

all:$(TARGET)

$(TARGET):$(SOURCE)
	$(CC) $(SOURCE) -o $(TARGET) $(LIBS) $(CFLAGS) $(COMIPLEFLAGS)

clean:
	touch $(TARGET)
	rm $(TARGET)
	touch $(TARGET).root
	rm $(TARGET).root
	rm *~
