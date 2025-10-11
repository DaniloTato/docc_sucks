#include "knapsack.hpp"

#include <algorithm>

/**
 * Solves the 0/1 Knapsack problem using dynamic programming.
 *
 * Being n the number of items.
 *
 * Complexity
 * 
 * Given that we iterate over a 1D array for dynamic programming:
 * Time Complexity: O(n * capacity).
 *
 * This would intuitively lead us to believe that the space complexity is also
 *   O(n * capacity). However, we can optimize the space complexity to O(capacity)
 *   by using a single array and iterating backwards through it. This way, we
 *   ensure that each state is computed based on the results of the previous item,
 *   thus avoiding overwriting values that are still needed for future computations.

 * Space Complexity: O(capacity)
 */

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
