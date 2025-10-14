#include "tsp_io.hpp"
#include <cmath>
#include <sstream>
#include <numeric>
#include <random>
#include <algorithm>
#include <iostream>

using ll = long long;

static inline ll dist_round(const Point &a, const Point &b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    double d = std::sqrt(dx * dx + dy * dy);
    return (ll)std::llround(d);
}

std::vector<Point> read_tsp_from_stdin() {
    std::vector<Point> pts;
    std::string line;
    bool in_coords = false;

    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;
        std::string s = line;
        while (!s.empty() && isspace((unsigned char)s.front())) s.erase(s.begin());

        if (!in_coords) {
            std::string up = s;
            for (auto &c: up) c = toupper((unsigned char)c);
            if (up.rfind("NODE_COORD_SECTION", 0) == 0) {
                in_coords = true;
                continue;
            }
        } else {
            std::stringstream ss(s);
            int id; double x, y;
            if (!(ss >> id >> x >> y)) break;
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

std::vector<std::vector<ll>> compute_dist_matrix(const std::vector<Point>& pts) {
    int n = pts.size();
    std::vector<std::vector<ll>> d(n, std::vector<ll>(n));
    for (int i = 0; i < n; i++) {
        d[i][i] = 0;
        for (int j = i + 1; j < n; j++) {
            ll dd = dist_round(pts[i], pts[j]);
            d[i][j] = d[j][i] = dd;
        }
    }
    return d;
}