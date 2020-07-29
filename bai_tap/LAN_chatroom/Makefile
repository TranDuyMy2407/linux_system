CC = gcc
LIB = -pthread
SRC_DIR = src
INC = inc/sock_define.h
OUTPUT_DIR = output

all: $(OUTPUT_DIR)/server $(OUTPUT_DIR)/client

$(OUTPUT_DIR)/server:	server.o sock_define.o $(INC)
	$(CC) -o  $@ server.o sock_define.o $(LIB) 

server.o: $(SRC_DIR)/server.c
	gcc -c $<

sock_define.o: $(SRC_DIR)/sock_define.c 
	gcc -c $<

$(OUTPUT_DIR)/client:	client.o sock_define.o  $(INC)
	$(CC) -o $@ client.o sock_define.o $(LIB) 
	rm *.o

client.o: $(SRC_DIR)/client.c
	$(CC) -c $<




	

