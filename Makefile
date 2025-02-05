# Compiler and flags
CC = gcc
CFLAGS = -I./src/types
LDFLAGS = -lgmp

# Detect the operating system
ifeq ($(OS),Windows_NT)
    CFLAGS += -D_WIN32
    LDFLAGS += -lws2_32
else
    CFLAGS += -D__linux__
endif

# Directories
SRC_DIR = ./src
OBJ_DIR = ./obj
BIN_DIR = ./bin

# Target executable
TARGET = $(BIN_DIR)/main

# Source files
SRCS = $(wildcard $(SRC_DIR)/algorithms/*.c) \
       ./main.c \
       $(SRC_DIR)/plugins/plugin_manager.c \
       tests/benchmark.c \
       $(wildcard $(SRC_DIR)/file_func/*.c)

# Object files
OBJS = $(patsubst $(SRC_DIR)/algorithms/%.c, $(OBJ_DIR)/algorithms/%.o, $(wildcard $(SRC_DIR)/algorithms/*.c)) \
       $(OBJ_DIR)/main.o \
       $(OBJ_DIR)/plugins/plugin_manager.o \
       $(OBJ_DIR)/benchmark.o \
       $(patsubst $(SRC_DIR)/file_func/%.c, $(OBJ_DIR)/file_func/%.o, $(wildcard $(SRC_DIR)/file_func/*.c))

# Default target
all: $(TARGET)

# Rule to build the target
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Rule to build object files for algorithms
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

# Rule to build object file for benchmark.c
$(OBJ_DIR)/benchmark.o: tests/benchmark.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to build object files for file_func
$(OBJ_DIR)/file_func/%.o: $(SRC_DIR)/file_func/%.c
	@mkdir -p $(OBJ_DIR)/file_func
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Phony targets
.PHONY: all clean