# Makefile - A Makefile for the project 2 program
# Variable definitions
CC = gcc
CFLAGS = -g -c
LFLAGS = -o
TARGET = main
OBJECTS = main.o interface.o basic_operations.o h_functions.o
JUNK_FILES = *.dat *.core
INCLUDES = 
LIBS = 
all: $(OBJECTS) $(TARGET)

$(TARGET) : $(OBJECTS)
			$(CC) $(LFLAGS) $(TARGET) $(OBJECTS) $(INCLUDES) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) $*.c

clean:
		rm -f $(OBJECTS) $(TARGET) $(JUNK_FILES)

run:
		./$(TARGET)