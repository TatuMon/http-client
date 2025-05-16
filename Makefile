TARGET = http-client
SRC_DIR = ./src
BUILD_DIR = ./build
CC = gcc

all: $(TARGET)

run:
	$(BUILD_DIR)/$(TARGET)

$(TARGET): $(SRC_DIR)/main.c $(SRC_DIR)/conn.c $(SRC_DIR)/utils.c
	mkdir -p $(BUILD_DIR)
	$(CC) $^ -o $(BUILD_DIR)/$(TARGET)

clean:
	rm build/*

