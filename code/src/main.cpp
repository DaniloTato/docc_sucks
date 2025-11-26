#include "aco.hpp"
#include "io.hpp"

#include <chrono>
#include <iostream>
#include <vector>

// choose globally how big random tests are
static const int GLOBAL_N = 50;

int main() {
    TSP_SUBSET_SIZE = GLOBAL_N;

    unsigned seed = static_cast<unsigned>(
        std::chrono::system_clock::now().time_since_epoch().count());

    // read full instance
    auto pts_all = read_tsp_from_stdin();
    if (pts_all.empty()) {
        std::cerr << "No points read.\n";
        return 1;
    }

    // Number of random trials you want
    int trials = 5;

    for (int t = 0; t < trials; ++t) {
        // === build random subinstance ===
        auto pts = build_random_subset(pts_all, seed + t);
        auto dist = compute_dist_matrix(pts);

        int N = (int)pts.size();
        int numAnts = N;
        int maxIterations = 200;

        auto start = std::chrono::high_resolution_clock::now();
        auto result = run_aco(dist, numAnts, maxIterations, seed + t);
        auto end = std::chrono::high_resolution_clock::now();

        long long elapsed =
            std::chrono::duration_cast<std::chrono::microseconds>(end - start)
                .count();

        const long long bestCost = result.first;
        const auto &bestTour = result.second;

        std::cout << "ALGO=ACO"
                  << " trial=" << t << " N=" << N << " SEED=" << seed + t
                  << " COST=" << bestCost << " TIME_us=" << elapsed
                  << " TOUR_LEN=" << bestTour.size() << "\n";
    }

    return 0;
}
