CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Iinclude
BUILD_DIR = build
SRC_DIR = src

OBJS = $(BUILD_DIR)/main.o $(BUILD_DIR)/tsp_io.o $(BUILD_DIR)/tsp_algorithms.o
TARGET = $(BUILD_DIR)/tsp

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(BUILD_DIR)/*.o $(TARGET)

# Default run parameters
N ?= 500
INPUT ?= tests/dsj1000.tsp

run: $(TARGET)
	@echo "Running: ./$(TARGET) $(N) < $(INPUT)"
	./$(TARGET) $(N) < $(INPUT)