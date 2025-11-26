#include "io.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <random>
#include <sstream>
#include <string>

int TSP_SUBSET_SIZE = 0;

using ll = long long;

static inline ll dist_round(const Point &a, const Point &b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    double d = std::sqrt(dx * dx + dy * dy);
    return static_cast<ll>(std::llround(d));
}

std::vector<Point> read_tsp_from_stdin() {
    std::vector<Point> pts;
    std::string line;
    bool in_coords = false;

    while (std::getline(std::cin, line)) {
        if (line.empty())
            continue;

        std::string s = line;
        while (!s.empty() &&
               std::isspace(static_cast<unsigned char>(s.front()))) {
            s.erase(s.begin());
        }

        if (!in_coords) {
            std::string up = s;
            for (auto &c : up) {
                c = static_cast<char>(
                    std::toupper(static_cast<unsigned char>(c)));
            }
            if (up.rfind("NODE_COORD_SECTION", 0) == 0) {
                in_coords = true;
                continue;
            }
        } else {
            std::stringstream ss(s);
            int id;
            double x, y;
            if (!(ss >> id >> x >> y))
                break;
            pts.push_back({id, x, y});
        }
    }

    return pts;
}

std::vector<int> sample_indices(int total, int N, unsigned seed) {
    std::vector<int> idx(total);
    std::iota(idx.begin(), idx.end(), 0);
    std::mt19937 rng(seed);
    std::shuffle(idx.begin(), idx.end(), rng);
    idx.resize(N);
    return idx;
}

std::vector<std::vector<ll>>
compute_dist_matrix(const std::vector<Point> &pts) {
    int n = static_cast<int>(pts.size());
    std::vector<std::vector<ll>> d(n, std::vector<ll>(n));

    for (int i = 0; i < n; ++i) {
        d[i][i] = 0;
        for (int j = i + 1; j < n; ++j) {
            ll dd = dist_round(pts[i], pts[j]);
            d[i][j] = d[j][i] = dd;
        }
    }

    return d;
}

std::vector<Point> build_random_subset(const std::vector<Point> &allPts,
                                       unsigned seed) {
    if (TSP_SUBSET_SIZE <= 0 || TSP_SUBSET_SIZE > (int)allPts.size()) {
        std::cerr << "Error: invalid TSP_SUBSET_SIZE=" << TSP_SUBSET_SIZE
                  << "\n";
        return {};
    }

    auto idx = sample_indices(allPts.size(), TSP_SUBSET_SIZE, seed);

    std::vector<Point> pts;
    pts.reserve(TSP_SUBSET_SIZE);
    for (int i = 0; i < TSP_SUBSET_SIZE; ++i) {
        Point p = allPts[idx[i]];
        p.id = i; // renumber to 0..N-1
        pts.push_back(p);
    }
    return pts;
}
