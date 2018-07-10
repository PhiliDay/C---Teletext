CFLAGS = `pkg-config --cflags --libs MagickWand` -O2 -Wall -Wextra -pedantic -ansi -Wfloat-equal
INCS = teletext.h
TARGET = extension
SOURCES =  $(TARGET).c
LIBS =  `pkg-config --cflags --libs MagickWand` -lm
CC = gcc


all: $(SOURCES)
	$(CC) -o $(TARGET) $(SOURCES) $(LIBS)

clean:
	rm -f $(TARGET)

run: all
	./$(TARGET) red.png
