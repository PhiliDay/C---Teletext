CFLAGS = `sdl2-config --cflags` -O2 -Wall -Wextra -pedantic -ansi -Wfloat-equal
INCS = teletext.h
TARGET = teletext
SOURCES =  $(TARGET).c
LIBS =  `sdl2-config --libs` -lm
CC = gcc


all: $(SOURCES) $(INCS)
	$(CC) $(SOURCES) -o $(TARGET) $(CFLAGS) $(LIBS)

clean:
	rm -f $(TARGET)

run: all
	./$(TARGET) test.m7
	./$(TARGET) testFile.m7
