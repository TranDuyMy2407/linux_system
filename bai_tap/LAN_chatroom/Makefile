CC = gcc
LIB = -pthread
SRC_DIR = src
INC_DIR = inc
OBJ_DIR = obj
OUTPUT_DIR = output

INC_FILE = inc/sock_define.h



all:  $(OUTPUT_DIR)/server $(OUTPUT_DIR)/client

$(OUTPUT_DIR)/server: $(OBJ_DIR)/server.o $(OBJ_DIR)/sock_define.o 
	$(CC) -o  $@ $(OBJ_DIR)/server.o $(OBJ_DIR)/sock_define.o   $(LIB)

$(OBJ_DIR)/server.o: $(SRC_DIR)/server.c $(INC_DIR)
	$(CC) -c -o $@ $< $(INC) -I $(INC_DIR)


$(OUTPUT_DIR)/client: $(OBJ_DIR)/client.o $(OBJ_DIR)/sock_define.o 
	$(CC) -o $@ $(OBJ_DIR)/client.o $(OBJ_DIR)/sock_define.o  $(LIB) 

$(OBJ_DIR)/client.o: $(SRC_DIR)/client.c $(INC_DIR)
	$(CC) -c -o $@  $< -I $(INC_DIR)


$(OBJ_DIR)/sock_define.o: $(SRC_DIR)/sock_define.c $(INC_DIR)
	$(CC) -c -o  $@ $< -I $(INC_DIR)

clean: 
	rm $(OUTPUT_DIR)/* $(OBJ_DIR)/*


	

