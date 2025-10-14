#ifndef TSP_IO_H
#define TSP_IO_H

#include <vector>

struct Point {
    int id;
    double x, y;
};

std::vector<Point> read_tsp_from_stdin();
std::vector<int> sample_indices(int total, int N, unsigned seed);
std::vector<std::vector<long long>> compute_dist_matrix(const std::vector<Point>& pts);

#endif