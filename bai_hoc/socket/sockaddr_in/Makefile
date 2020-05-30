CC = gcc
LIB = -pthread

all:	server client

server:	server.o 
	$(CC) -o server server.o $(LIB)

server.o: server.c
	$(CC) -c server.c 

client:	client.o 
	$(CC) -o client client.o $(LIB)

client.o: client.c 
	$(CC) -c client.c 


