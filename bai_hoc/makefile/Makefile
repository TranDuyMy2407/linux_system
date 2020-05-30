CC = gcc
OBJS = hello.o main.o
INC_FILES = hello.h 
TARGET = main

%.o: %.c $(INC_FILES)
	$(CC) -c -o  $@ $<

$(TARGET): hello.o main.o
	$(CC) -o $@ hello.o main.o


clean: 
	rm $(TARGET) *.o



