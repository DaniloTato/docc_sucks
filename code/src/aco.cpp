#include "aco.hpp"

#include <algorithm>
#include <cmath>
#include <limits>
#include <random>
#include <vector>

namespace {

using ll = long long;
using std::vector;

struct Ant {
    vector<int> tour;
    vector<bool> visited;
    ll length = std::numeric_limits<ll>::max();
};

class ACO {
  public:
    ACO(const vector<vector<ll>> &dist, int numAnts, int maxIterations,
        unsigned seed)
        : n_(static_cast<int>(dist.size())), numAnts_(numAnts),
          maxIterations_(maxIterations), alpha_(1.0), beta_(5.0), rho_(0.5),
          Q_(100.0), initialPheromone_(1.0), dist_(dist),
          pheromone_(n_, vector<double>(n_, initialPheromone_)),
          heuristic_(n_, vector<double>(n_, 0.0)), ants_(numAnts_),
          bestTour_(n_), bestLength_(std::numeric_limits<ll>::max()),
          rng_(seed) {
        initializeHeuristic();
    }

    std::pair<ll, vector<int>> run() {
        for (int iter = 0; iter < maxIterations_; ++iter) {
            // Construct tours for all ants
            for (int k = 0; k < numAnts_; ++k) {
                constructTour(ants_[k]);

                // Optional local optimization
                // twoOptImprove(ants_[k].tour);
                // ants_[k].length = computeTourLength(ants_[k].tour);

                if (ants_[k].length < bestLength_ &&
                    isValidTour(ants_[k].tour)) {
                    bestLength_ = ants_[k].length;
                    bestTour_ = ants_[k].tour;
                }
            }

            // Global pheromone update
            updatePheromones();
        }

        return {bestLength_, bestTour_};
    }

  private:
    int n_;
    int numAnts_;
    int maxIterations_;

    // ACO parameters
    double alpha_;
    double beta_;
    double rho_;
    double Q_;
    double initialPheromone_;

    const vector<vector<ll>> &dist_;
    vector<vector<double>> pheromone_;
    vector<vector<double>> heuristic_;

    vector<Ant> ants_;
    vector<int> bestTour_;
    ll bestLength_;

    std::mt19937 rng_;

    void initializeHeuristic() {
        // heuristic[i][j] = 1.0 / distance(i,j)
        for (int i = 0; i < n_; ++i) {
            for (int j = 0; j < n_; ++j) {
                if (i == j || dist_[i][j] == 0) {
                    heuristic_[i][j] = 0.0;
                } else {
                    heuristic_[i][j] = 1.0 / static_cast<double>(dist_[i][j]);
                }
            }
        }
    }

    ll computeTourLength(const vector<int> &tour) const {
        ll L = 0;
        for (int i = 0; i < n_ - 1; ++i) {
            L += dist_[tour[i]][tour[i + 1]];
        }
        // return to start
        L += dist_[tour.back()][tour.front()];
        return L;
    }

    bool isValidTour(const vector<int> &tour) const {
        if (static_cast<int>(tour.size()) != n_)
            return false;
        vector<bool> seen(n_, false);
        for (int city : tour) {
            if (city < 0 || city >= n_)
                return false;
            if (seen[city])
                return false;
            seen[city] = true;
        }
        return true;
    }

    int selectNextCity(int current, const Ant &ant) {
        vector<int> candidates;
        candidates.reserve(n_);
        for (int j = 0; j < n_; ++j) {
            if (!ant.visited[j]) {
                candidates.push_back(j);
            }
        }

        // If only one candidate, pick it directly
        if (candidates.size() == 1) {
            return candidates[0];
        }

        // Compute weights based on pheromone and heuristic
        vector<double> weight(candidates.size());
        double sumW = 0.0;
        for (size_t idx = 0; idx < candidates.size(); ++idx) {
            int j = candidates[idx];
            double tau = pheromone_[current][j];
            double eta = heuristic_[current][j];
            double w = std::pow(tau, alpha_) * std::pow(eta, beta_);
            weight[idx] = w;
            sumW += w;
        }

        // If everything is zero (pathological), choose uniform random
        if (sumW <= 0.0) {
            std::uniform_int_distribution<int> uni(
                0, static_cast<int>(candidates.size()) - 1);
            return candidates[uni(rng_)];
        }

        // Roulette wheel selection
        std::uniform_real_distribution<double> distR(0.0, sumW);
        double r = distR(rng_);
        double cumulative = 0.0;
        for (size_t idx = 0; idx < candidates.size(); ++idx) {
            cumulative += weight[idx];
            if (cumulative >= r) {
                return candidates[idx];
            }
        }

        // Numerical safety
        return candidates.back();
    }

    void constructTour(Ant &ant) {
        ant.tour.clear();
        ant.visited.assign(n_, false);

        // Random start city
        std::uniform_int_distribution<int> startDist(0, n_ - 1);
        int start = startDist(rng_);

        ant.tour.push_back(start);
        ant.visited[start] = true;

        int current = start;
        for (int step = 1; step < n_; ++step) {
            int nextCity = selectNextCity(current, ant);
            ant.tour.push_back(nextCity);
            ant.visited[nextCity] = true;
            current = nextCity;
        }

        ant.length = computeTourLength(ant.tour);
    }

    void updatePheromones() {
        // Evaporation
        for (int i = 0; i < n_; ++i) {
            for (int j = 0; j < n_; ++j) {
                pheromone_[i][j] *= (1.0 - rho_);
            }
        }

        // Deposit pheromone for each ant
        for (const Ant &ant : ants_) {
            double deposit = Q_ / static_cast<double>(ant.length);
            const vector<int> &t = ant.tour;

            for (int i = 0; i < n_ - 1; ++i) {
                int a = t[i];
                int b = t[i + 1];
                pheromone_[a][b] += deposit;
                pheromone_[b][a] += deposit;
            }

            // return edge
            int last = t.back();
            int first = t.front();
            pheromone_[last][first] += deposit;
            pheromone_[first][last] += deposit;
        }
    }

    // Optional 2-opt improvement (not used by default)
    void twoOptImprove(vector<int> &tour) {
        bool improved = true;
        while (improved) {
            improved = false;
            double bestDelta = 0.0;
            int bestI = -1, bestK = -1;

            for (int i = 0; i < n_ - 1; ++i) {
                for (int k = i + 2; k < n_; ++k) {
                    int i1 = tour[i];
                    int j1 = tour[(i + 1) % n_];
                    int i2 = tour[k];
                    int j2 = tour[(k + 1) % n_];

                    double before =
                        static_cast<double>(dist_[i1][j1] + dist_[i2][j2]);
                    double after =
                        static_cast<double>(dist_[i1][i2] + dist_[j1][j2]);

                    double delta = after - before;
                    if (delta < bestDelta) {
                        bestDelta = delta;
                        bestI = i + 1;
                        bestK = k;
                        improved = true;
                    }
                }
            }

            if (improved && bestI >= 0 && bestK >= 0) {
                std::reverse(tour.begin() + bestI, tour.begin() + bestK + 1);
            }
        }
    }
};

} // namespace

std::pair<long long, std::vector<int>>
run_aco(const std::vector<std::vector<long long>> &dist, int numAnts,
        int maxIterations, unsigned seed) {
    ACO aco(dist, numAnts, maxIterations, seed);
    return aco.run();
}
