TARGET = http1.1-client
BUILD_DIR = ./build
CC = gcc

all: $(TARGET)

run:
	$(BUILD_DIR)/$(TARGET)

$(TARGET): main.c
	mkdir -p $(BUILD_DIR)
	$(CC) main.c -o $(BUILD_DIR)/$(TARGET)

clean:
	rm build/*

