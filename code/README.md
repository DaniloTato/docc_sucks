# Activity 5.1 Ant Colony Optimization and TSP

This project contains a C++ implementation of the Ant Colony Algorithm
algorithm applied to the Traveling Salesman Problem.

## Project Structure

```
project_root/
├── src/
│   ├── main.cpp
│   ├── tsp_algorithms.cpp
│   └── tsp_io.cpp
├── include/
│   ├── tsp_algorithms.hpp
│   └── tsp_io.hpp
├── tests/
│   └── dsj1000.tsp
├── build/
├── table.py
├── Makefile
└── README.md
```

## C++ Compilation

### Manual Compilation

Assuming you have `g++` installed:

```bash
# Compile source files
g++ -std=c++17 -O2 -Iinclude -c src/tsp_algorithms.cpp -o tsp_algorithms.o
g++ -std=c++17 -O2 -Iinclude -c src/tsp_io.cpp -o tsp_io.o
g++ -std=c++17 -O2 -Iinclude -c src/main.cpp -o main.o

# Link objects
g++ -std=c++17 -O2 -o build/tsp main.o tsp_algorithms.o tsp_io.o
```

### Using Makefile

```bash
# Compile and link
make

# Run with sample input
make run ARGS="500 < tests/dsj1000.tsp"
```

- `make` will compile the program and produce `build/tsp`
- `make run` will execute the program using the redirected input from `dsj1000.tsp`

### Usage

```bash
./build/tsp <ALGO: NN|CL|MST> <N> < <dataset.tsp>
```

- `ALGO`: Choose the algorithm (`NN`, `CL`, `MST`)
- `N`: Number of cities to sample
- Input is redirected from a `.tsp` file

Example:

```bash
./build/tsp NN 100 < tests/dsj1000.tsp
```

## Python Experiment Script

`table.py` runs the compiled TSP program for different `N` values, computes cost and time statistics, and outputs a table with mean and standard deviation.

### Setup

1. Create a virtual environment:

```bash
python3 -m venv venv
source venv/bin/activate
```

2. Install dependencies:

```bash
pip install pandas
```

### Usage

```bash
python table.py
```

- Make sure `build/tsp` is compiled before running.
- The script reads `dsj1000.tsp` and runs experiments for multiple `N` values.
- Generates a table showing `COST` and `TIME_us` (mean and std) for each algorithm.

## Notes

- The C++ program uses a random seed based on system time, ensuring reproducibility within a single run for all algorithms.
- Adjust `N` values and number of repetitions directly in `table.py` if desired.
