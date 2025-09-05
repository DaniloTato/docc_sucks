# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -g

# Directories
src_dir := src
build_dir := build

# Source files and object files
src := $(shell find $(src_dir) -name '*.cpp')
obj := $(src:$(src_dir)/%.cpp=$(build_dir)/%.o)

# Target executable
target := $(build_dir)/main

# Default rule
all: $(target)

# Run the program
run: $(target)
	@./$^

test: $(target)
	@./test.py --exe $(target)

# Link objects into executable
$(target): $(obj) | $(build_dir)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile .cpp into .o in the build directory (mirrors source tree)
$(build_dir)/%.o: $(src_dir)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(build_dir):
	@mkdir $@

# Clean build files
clean:
	@rm -rf $(build_dir)

.PHONY: all run test debug clean
