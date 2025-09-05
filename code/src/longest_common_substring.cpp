#include "checks.hpp"
#include <array>
#include <vector>

struct SAMState {
    int link = -1;
    int len = 0;
    int first_pos = -1;
    std::array<int, 256> next;
    SAMState() { next.fill(-1); }
};

// Substring Automaton
range longest_common_substr(const string &seq_a, const string &seq_b) {
    const int n = static_cast<int>(seq_a.size());
    const int m = static_cast<int>(seq_b.size());
    if (n == 0 || m == 0)
        return make_range(0, 0);

    std::vector<SAMState> st;
    st.reserve(2 * n);
    st.emplace_back();
    int last = 0;

    for (int i = 0; i < n; ++i) {
        unsigned char c = static_cast<unsigned char>(seq_a[i]);
        int cur = static_cast<int>(st.size());
        st.emplace_back();
        st[cur].len = st[last].len + 1;
        st[cur].first_pos = i;

        int p = last;
        while (p != -1 && st[p].next[c] == -1) {
            st[p].next[c] = cur;
            p = st[p].link;
        }
        if (p == -1) {
            st[cur].link = 0;
        } else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } else {
                int clone = static_cast<int>(st.size());
                st.push_back(st[q]);
                st[clone].len = st[p].len + 1;
                // keep first_pos of q
                while (p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }

    int v = 0, L = 0, best_len = 0, best_state = 0;
    for (int i = 0; i < m; ++i) {
        unsigned char c = static_cast<unsigned char>(seq_b[i]);
        while (v && st[v].next[c] == -1) {
            v = st[v].link;
            L = st[v].len;
        }
        if (st[v].next[c] != -1) {
            v = st[v].next[c];
            ++L;
        } else {
            v = 0;
            L = 0;
        }
        if (L > best_len) {
            best_len = L;
            best_state = v;
        }
    }

    if (best_len == 0)
        return make_range(0, 0);
    int end_a = st[best_state].first_pos;
    int start_a = end_a - best_len + 1;
    return make_range(start_a, start_a + best_len);
}
