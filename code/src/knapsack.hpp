#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <vector>

using std::vector;

typedef long long lli;

typedef size_t weight;

lli knapsack(size_t n, vector<lli> values, vector<weight> weights,
             weight capacity);

#endif // !KNAPSACK_H
