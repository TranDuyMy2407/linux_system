CC = gcc
LIB = -pthread
INC_FILE = sock_define.h

all: server client
server:	server.o sock_define.o $(INC_FILE)
	$(CC) -o  $@ server.o sock_define.o $(LIB) -I.

server.o: server.c
	gcc -c $<

sock_define.o: sock_define.c 
	gcc -c $<

client: client.o sock_define.o  $(INC_FILE)
	$(CC) -o $@ client.o sock_define.o $(LIB) -I.

client.o: client.c
	gcc -c $<

clean:
	rm *.o

	

