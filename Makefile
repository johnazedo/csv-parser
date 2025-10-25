# Makefile for csv-parser project

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2 -Iinclude
DEBUG_FLAGS = -g -DDEBUG
LDFLAGS =

# Directories
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
DATA_DIR = data
BIN_DIR = .

# Project name
TARGET = $(BIN_DIR)/csv-parser

# Source files
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/utils.c
OBJS = $(BUILD_DIR)/main.o $(BUILD_DIR)/utils.o
HEADERS = $(INC_DIR)/utils.h $(INC_DIR)/values.h

# Default target
all: $(BUILD_DIR) $(TARGET)

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Build the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compile source files to object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Debug build
debug: CFLAGS += $(DEBUG_FLAGS)
debug: clean $(TARGET)

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Run the program with file.csv
run: $(TARGET)
	./$(TARGET) $(DATA_DIR)/file.csv

# Run the program with stocks.csv
run-stocks: $(TARGET)
	./$(TARGET) $(DATA_DIR)/stocks.csv

# Install (optional - installs to /usr/local/bin)
install: $(TARGET)
	install -m 755 $(TARGET) /usr/local/bin/

# Uninstall
uninstall:
	rm -f /usr/local/bin/$(TARGET)

# Rebuild everything
rebuild: clean all

# Show help
help:
	@echo "Available targets:"
	@echo "  all          - Build the project (default)"
	@echo "  debug        - Build with debug symbols"
	@echo "  clean        - Remove build artifacts"
	@echo "  run          - Build and run with file.csv"
	@echo "  run-stocks   - Build and run with stocks.csv"
	@echo "  install      - Install to /usr/local/bin"
	@echo "  uninstall    - Remove from /usr/local/bin"
	@echo "  rebuild      - Clean and rebuild"
	@echo "  help         - Show this help message"

# Phony targets (not actual files)
.PHONY: all clean debug run run-stocks install uninstall rebuild help
