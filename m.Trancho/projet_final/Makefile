# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -O2 -I/opt/homebrew/Cellar/gmp/6.3.0/include
LDFLAGS = -L/opt/homebrew/Cellar/gmp/6.3.0/lib -lgmp

# Target executable
TARGET = main

# Source files
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Rule to build the target
$(TARGET): $(OBJS)
    $(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJS)

# Rule to build object files
%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
    rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean