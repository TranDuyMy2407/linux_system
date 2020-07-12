CC = gcc
SRC_DIR = src
OUTPUT_DIR = output

$(OUTPUT_DIR)/hello: $(OUTPUT_DIR)/hello.o
	$(CC) -o $@ $<

$(OUTPUT_DIR)/hello.o: $(OUTPUT_DIR)/hello.s
	$(CC) -c -o $@  $<


$(OUTPUT_DIR)/hello.s: $(SRC_DIR)/hello.c
	$(CC) -S -o $@  $<


clean:
	rm -rf $(OUTPUT_DIR)/*

