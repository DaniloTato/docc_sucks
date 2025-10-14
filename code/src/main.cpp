#include "tsp_io.hpp"
#include "tsp_algorithms.hpp"
#include <chrono>
#include <random>
#include <iostream>
#include <vector>
#include <string>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <N> < <input_file>\n";
        return 1;
    }

    int N = std::stoi(argv[1]);
    unsigned seed = static_cast<unsigned>(
        std::chrono::system_clock::now().time_since_epoch().count()
    );

    auto pts_all = read_tsp_from_stdin();
    if (pts_all.empty()) {
        std::cerr << "No points read from stdin.\n";
        return 1;
    }

    // Sample indices once
    auto idx = sample_indices(pts_all.size(), N, seed);
    std::vector<Point> pts;
    pts.reserve(N);
    for (int i = 0; i < N; i++) {
        Point p = pts_all[idx[i]];
        p.id = i;
        pts.push_back(p);
    }

    auto d = compute_dist_matrix(pts);

    std::vector<std::string> algos = {"NN","CL","MST"};
    for (auto &algo : algos) {
        auto start = std::chrono::high_resolution_clock::now();

        std::pair<long long, std::vector<int>> result;
        if (algo == "NN") {
            std::mt19937 rng(seed);
            int start_idx = rng() % N;
            result = nearest_neighbor(d, start_idx);
        } else if (algo == "CL") {
            result = cheapest_link(d);
        } else if (algo == "MST") {
            result = mst_tsp(d);
        }

        auto end = std::chrono::high_resolution_clock::now();
        long long elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        std::cout << "ALGO=" << algo
                  << " N=" << N
                  << " SEED=" << seed
                  << " COST=" << result.first
                  << " TIME_in_micro_s=" << elapsed
                  << " TOUR_LEN=" << (int)result.second.size() - 1
                  << "\n";
    }

    return 0;
}