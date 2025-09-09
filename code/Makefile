# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -g

# Directories
src_dir := src
build_dir := build
tests_dir := tests

# Source files and object files
src := $(shell find $(src_dir) -name '*.cpp')
obj := $(src:$(src_dir)/%.cpp=$(build_dir)/%.o)

gen_tests := gen_tests.sh

target := $(build_dir)/main

all: $(target)

run: $(target)
	@./$^

debug: $(target)
	@gdb ./$^

test: $(target) | $(tests_dir)
	@./test.py $(target)

.PHONY: all run test debug clean

$(target): $(obj) | $(build_dir)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(build_dir)/%.o: $(src_dir)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(build_dir):
	@mkdir $@

$(tests_dir): $(gen_tests)
	@./$^

clean:
	@rm -rf $(build_dir)

.PHONY: clean
