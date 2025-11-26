#ifndef IO_HPP
#define IO_HPP

#include <vector>

struct Point {
    int id;
    double x, y;
};

// GLOBAL size of subproblem
extern int TSP_SUBSET_SIZE;

// I/O utilities
std::vector<Point> read_tsp_from_stdin();
std::vector<int> sample_indices(int total, int N, unsigned seed);
std::vector<std::vector<long long>>
compute_dist_matrix(const std::vector<Point> &pts);

// NEW: build a random subset (renumber 0..N-1)
std::vector<Point> build_random_subset(const std::vector<Point> &allPts,
                                       unsigned seed);

#endif
