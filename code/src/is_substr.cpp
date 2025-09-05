#include "checks.hpp"

int is_substr(const string &seq, const string &sub) {
    int m = seq.size();
    int n = sub.size();

    vector<int> badchar(ASCII_SIZE, -1);
    vector<range> answer;

    for (int i = 0; i < m; i++) {
        badchar[(int)seq[i]] = i;
    }

    int s = 0;
    while (s + m < n) {
        int j = m - 1;

        while (j >= 0 && seq[j] == sub[s + j])
            j--;

        char next_char_after_pattern = sub[s + m];
        int next_char_value = badchar[next_char_after_pattern];
        if (j < 0) {
            answer.push_back(std::make_pair(s, s + m - 1));
            int next_char_value = badchar[next_char_after_pattern];
            if (s + m < n)
                s += m - next_char_value;
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
