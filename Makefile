# Variables
BUILD_DIR := build
BIN_DIR := $(BUILD_DIR)/bin
EXECUTABLE := FizzleFramework

.PHONY: all ensure_build_dir build run clean

# Default target
all: run

# Ensure build directory exists
ensure_build_dir:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)

# Build target
build: ensure_build_dir
	@cd $(BUILD_DIR) && cmake .. && cmake --build .

# Run target
run: build
	@$(BIN_DIR)/$(EXECUTABLE)

# Clean (remove build directory)
clean:
	@rm -rf $(BUILD_DIR)

# Run the game and then clean
run_and_clean: run
	@$(MAKE) clean
