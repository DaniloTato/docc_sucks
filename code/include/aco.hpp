#ifndef ACO_HPP
#define ACO_HPP

#include <utility>
#include <vector>

// Run Ant Colony Optimization on a TSP distance matrix.
//
// dist: square matrix dist[i][j] with distances (long long).
// numAnts: number of ants used per iteration.
// maxIterations: number of iterations of the algorithm.
// seed: random seed.
//
// Returns: (best_cost, best_tour) where best_tour is a permutation of 0..n-1
//          representing the cycle in order; the cost already includes return
//          from last city to first.
std::pair<long long, std::vector<int>>
run_aco(const std::vector<std::vector<long long>> &dist, int numAnts,
        int maxIterations, unsigned seed);

#endif // ACO_HPP
