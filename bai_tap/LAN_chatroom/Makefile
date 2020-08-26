CC = gcc
LIB = -pthread
SRC_DIR = src
INC = inc/sock_define.h
OBJ_DIR = obj
OUTPUT_DIR = output

all: $(OUTPUT_DIR)/server $(OUTPUT_DIR)/client

$(OUTPUT_DIR)/server: $(OBJ_DIR)/server.o $(OBJ_DIR)/sock_define.o $(INC)
	$(CC) -o  $@ $(OBJ_DIR)/server.o $(OBJ_DIR)/sock_define.o $(LIB) 

$(OBJ_DIR)/server.o: $(SRC_DIR)/server.c
	$(CC) -c -o $@ $<


$(OUTPUT_DIR)/client: $(OBJ_DIR)/client.o $(OBJ_DIR)/sock_define.o  $(INC)
	$(CC) -o $@ $(OBJ_DIR)/client.o $(OBJ_DIR)/sock_define.o $(LIB) 

$(OBJ_DIR)/client.o: $(SRC_DIR)/client.c
	$(CC) -c -o $@  $<


$(OBJ_DIR)/sock_define.o: $(SRC_DIR)/sock_define.c 
	$(CC) -c -o  $@ $<

clean: 
	rm $(OUTPUT_DIR)/* $(OBJ_DIR)/*


	

