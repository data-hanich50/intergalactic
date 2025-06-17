# Compiler and flags
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic -Iinclude
LDFLAGS =

# Directories
SRC_DIR = source
INC_DIR = include
OBJ_DIR = build
BIN_DIR = bin

# Output executable name
TARGET = $(BIN_DIR)/main

# Find all source files
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Default rule
all: $(TARGET)

# Linking
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(LDFLAGS) -o $@ $^ -lm

# Compilation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)

.PHONY: all clean
