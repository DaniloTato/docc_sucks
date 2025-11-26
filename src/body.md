# Ant Colony Optimization (ACO) for the Traveling Salesman Problem (TSP)

## 1. Objective

This project applies Ant Colony Optimization (ACO) to the Traveling Salesman Problem (TSP). The algorithm was implemented in C++ and tested using TSPLIB-style input files.

---

## 2. ACO Design Summary

| Component                  | Description                                                                                                     |
| -------------------------- | --------------------------------------------------------------------------------------------------------------- |
| Data Model                 | Cities are read as points. A distance matrix is computed using rounded Euclidean distance.                      |
| Initialization             | Pheromone levels are initialized uniformly.                                                                     |
| Solution Construction      | Each ant builds a tour using a probability that depends on pheromone level and heuristic weight (1 / distance). |
| Pheromone Update           | Pheromones evaporate and are reinforced based on tour quality (Q / length).                                     |
| Validation and Improvement | Tours are verified to contain each city once. A 2-opt local improvement step is not yet enabled.                |

The code was split into modules: `aco.*`, `io.*`, and `main.cpp`.

---

## 3. Testing and Results

Dataset: `dsj1000.tsp`\
Random samples of 50 cities were selected for each trial.\
Each execution produced 5 independent runs.

### Captured Results

| Execution | Best Cost (range) | Time (microseconds) | Notes                                       |
| --------- | ----------------- | ------------------- | ------------------------------------------- |
| 1         | 5.07M to 5.65M    | about 700000        | Different outcomes depending on random seed |
| 2         | 4.89M to 5.53M    | about 700000        | One very good sample close to 4.9M          |
| 3         | 5.21M to 5.56M    | about 700000        | Results centered near middle values         |

Observations:

- Execution time is very consistent (around 700k microseconds).
- Result quality varies because of random exploration.
- Typical best results were close to 5,000,000 for the 50-city subsets.

---

## 4. Conclusions and Future Work

- The ACO implementation generates valid tours and acceptable results on random TSP subsets.
- Result quality depends on random seed, which suggests improvements such as:
  - running more iterations or using elitist pheromone updates,
  - enabling a local search improvement such as 2-opt,
  - tuning parameters such as alpha, beta, rho, and number of ants.

---

## 5. References

- Dorigo, M. and Gambardella, L. M. (1997). "Ant Colony System: A Cooperative Learning Approach to the Traveling Salesman Problem."
- TSPLIB format reference.
