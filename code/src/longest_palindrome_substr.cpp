#include "checks.hpp"
#include <algorithm>

// range on [l r)
range longest_palindromic_substr(const string &seq) {
    const int n = seq.size();
    if (n == 0)
        return make_range(0, 0);

    string t;
    t.reserve(2 * n + 3);
    t.push_back('^');
    for (char c : seq) {
        t.push_back('#');
        t.push_back(c);
    }
    t.push_back('#');
    t.push_back('$');

    const int m = t.size();
    vector<int> P(m, 0);
    int center = 0, right = 0;

    for (int i = 1; i < m - 1; ++i) {
        if (i < right) {
            const int mirror = 2 * center - i;
            P[i] = std::min(right - i, P[mirror]);
        }
        while (t[i + 1 + P[i]] == t[i - 1 - P[i]])
            ++P[i];
        if (i + P[i] > right) {
            center = i;
            right = i + P[i];
        }
    }

    int maxLen = 0, centerIndex = 0;
    for (int i = 1; i < m - 1; ++i) {
        if (P[i] > maxLen) {
            maxLen = P[i];
            centerIndex = i;
        }
    }

    const int start = (centerIndex - maxLen) / 2;
    return make_range(start, start + maxLen);
}
