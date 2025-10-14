#ifndef TSP_ALGORITHMS_H
#define TSP_ALGORITHMS_H

#include <vector>
#include <utility>

std::pair<long long, std::vector<int>> nearest_neighbor(const std::vector<std::vector<long long>>& d, int start_idx);
std::pair<long long, std::vector<int>> mst_tsp(const std::vector<std::vector<long long>>& d);
std::pair<long long, std::vector<int>> cheapest_link(const std::vector<std::vector<long long>>& d);

#endif