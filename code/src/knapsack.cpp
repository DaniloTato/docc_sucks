#include "knapsack.hpp"

#include <algorithm>

lli knapsack(size_t n, vector<lli> values, vector<weight> weights,
             weight capacity) {
    vector<lli> dp(capacity + 1, 0);

    for (int i = 0; i < n; i++) {
        for (int w = capacity; w >= weights[i]; w--) {
            dp[w] = std::max(dp[w], values[i] + dp[w - weights[i]]);
        }
    }

    return dp[capacity];
}
