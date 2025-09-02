# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17

# Directories
SRC_DIR := src
BUILD_DIR := build

# Source files and object files
SRC := $(wildcard $(SRC_DIR)/**/*.cpp $(SRC_DIR)/*.cpp)
OBJ := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC))

# Target executable
TARGET := $(BUILD_DIR)/main

# Default rule
all: $(TARGET)

# Run the program
run: $(TARGET)
	@./$^

# Link objects into executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile .cpp into .o in the build directory (mirrors source tree)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean run
