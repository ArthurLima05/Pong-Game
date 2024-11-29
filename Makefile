
CC = gcc
CFLAGS = -Wall -g

SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

TARGET = $(BUILD_DIR)/pong


all: $(TARGET)

$(TARGET): $(BUILD_DIR)/main.o
    $(CC) $(CFLAGS) -o $(TARGET) $(BUILD_DIR)/main.o

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.c
    $(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $(SRC_DIR)/main.c -o $(BUILD_DIR)/main.o

clean:
    rm -f $(TARGET) $(BUILD_DIR)/*.o
