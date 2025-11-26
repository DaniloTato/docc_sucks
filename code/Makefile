CXX       := g++
CXXFLAGS  := -std=c++17 -O2 -Wall -Iinclude

SRC_DIR   := src
BUILD_DIR := build
TARGET    := $(BUILD_DIR)/tsp

CLANGDB   := compile_commands.json

MAKEFLAGS += --no-print-directory

# Find all source files and map them to object files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Default target
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Ensure build dir exists before compiling
$(BUILD_DIR):
	mkdir -p $@

# Generic rule for building any .o from src/
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean clean-clangdb clangdb run

clangdb: clean-clangdb
	@$(MAKE) $(CLANGDB)

$(CLANGDB):
	@$(MAKE) clean
	@bear -- $(MAKE) all

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

clean-clangdb:
	@rm -f $(CLANGDB)
	@rm -rf .cache/clangd

# Default run parameters
INPUT ?= tests/dsj1000.tsp

run: $(TARGET)
	@echo "./$(TARGET) < $(INPUT)"
	@./$(TARGET) < $(INPUT)
