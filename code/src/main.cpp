#include <iostream>

#include "knapsack.hpp"

int main() {
    size_t n;
    std::cin >> n;

    vector<lli> values(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> values[i];
    }

    vector<weight> weights(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> weights[i];
    }

    weight capacity;
    std::cin >> capacity;

    lli gain = knapsack(n, values, weights, capacity);
    std::cout << gain << std::endl;

    return 0;
}
