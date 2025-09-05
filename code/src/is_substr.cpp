#include "checks.hpp"

int is_substr(const string &seq, const string &sub) {
    int n = seq.size();
    int m = sub.size();

    if (n == 0 || m == 0)
        return -1;

    vector<int> badchar(ASCII_SIZE, -1);
    vector<range> answer;

    for (int i = 0; i < n; i++) {
        badchar[(int)seq[i]] = i;
    }

    int s = 0;
    while (s + n < m) {
        int j = n - 1;

        while (j >= 0 && seq[j] == sub[s + j])
            j--;

        char next_char_after_pattern = sub[s + n];
        int next_char_value = badchar[next_char_after_pattern];
        if (j < 0) {
            answer.push_back(std::make_pair(s, s + n - 1));
            int next_char_value = badchar[next_char_after_pattern];
            if (s + n < m)
                s += n - next_char_value;
            else
                s += 1;
        } else {
            if (j - next_char_value > 1)
                s += j - next_char_value;
            else
                s += 1;
        }
    }

    return answer.size() == 0 ? -1 : answer[0].first;
}
