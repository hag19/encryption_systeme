# Compiler and flags
CC = gcc
CFLAGS = -I/usr/include/x86_64-linux-gnu -I./src/types 
LDFLAGS = -L/usr/lib/x86_64-linux-gnu -lgmp 

# Directories
SRC_DIR = ./src
OBJ_DIR = ./obj
BIN_DIR = ./bin

# Target executable
TARGET = $(BIN_DIR)/main

# Source files
SRCS = $(wildcard $(SRC_DIR)/algorithms/*.c) ./main.c $(SRC_DIR)/plugins/plugin_manager.c
OBJS = $(patsubst $(SRC_DIR)/algorithms/%.c, $(OBJ_DIR)/algorithms/%.o, $(wildcard $(SRC_DIR)/algorithms/*.c)) $(OBJ_DIR)/main.o $(OBJ_DIR)/plugins/plugin_manager.o

# Default target
all: $(TARGET)

# Rule to build the target
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Rule to build object files
$(OBJ_DIR)/algorithms/%.o: $(SRC_DIR)/algorithms/%.c
	@mkdir -p $(OBJ_DIR)/algorithms
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to build object file for main.c
$(OBJ_DIR)/main.o: ./main.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to build object file for plugin_manager.c
$(OBJ_DIR)/plugins/plugin_manager.o: $(SRC_DIR)/plugins/plugin_manager.c
	@mkdir -p $(OBJ_DIR)/plugins
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Phony targets
.PHONY: all clean
