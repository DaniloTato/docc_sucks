# Activity 5.1 - Ant Colony Optimization for TSP

This project implements the Ant Colony Optimization (ACO) algorithm in C++ to
solve the Traveling Salesman Problem (TSP). The program reads TSPLIB-style
`.tsp` input from `stdin` and runs ACO on random subsets of the instance.

---

## Project Structure

```
src/
│── main.cpp    # runs multiple ACO trials
│── aco.cpp     # ACO implementation
│── io.cpp      # TSP input and utilities
include/
│── aco.hpp
│── io.hpp
tests/
│── dsj1000.tsp # sample TSPLIB instance
build/          # compiled output
Makefile
README.md
```

---

## Compilation and Execution

### Build

```bash
make
```

### Run (reads from stdin)

```bash
./build/tsp < tests/dsj1000.tsp
# or via make
make run
```

The program:

- reads the full TSP instance,
- randomly samples a fixed number of cities (constant N inside the code),
- executes several ACO trials with different seeds,
- prints cost and runtime per trial.

### Example Output

```
ALGO=ACO trial=0 N=50 SEED=... COST=... TIME_us=... TOUR_LEN=50
```
