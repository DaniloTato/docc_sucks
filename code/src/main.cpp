/*
 * Compute the Max-Flow using the Ford-Fulkerson algorithm using BFS, with time
 * complexity of O(V(E^2)) for V vertices and E edges
 * */

#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
typedef long long lli;

struct Edge {
    int to, rev;
    lli cap;
    Edge(int t, int r, lli c) : to(t), rev(r), cap(c) {}
};

struct Graph {
    int n;
    vector<vector<Edge>> g;
    Graph(int n_) : n(n_), g(n_) {}
    void add_edge(int u, int v, lli c) {
        g[u].emplace_back(v, (int)g[v].size(), c);
        g[v].emplace_back(u, (int)g[u].size() - 1, 0);
    }
    lli maxflow(int s, int t) {
        lli flow = 0;
        vector<int> pv(n), pe(n);
        while (true) {
            fill(pv.begin(), pv.end(), -1);
            queue<int> q;
            q.push(s);
            pv[s] = s;
            while (!q.empty() && pv[t] == -1) {
                int u = q.front();
                q.pop();
                for (int i = 0; i < (int)g[u].size(); ++i) {
                    Edge &e = g[u][i];
                    if (pv[e.to] == -1 && e.cap > 0) {
                        pv[e.to] = u;
                        pe[e.to] = i;
                        q.push(e.to);
                        if (e.to == t)
                            break;
                    }
                }
            }
            if (pv[t] == -1)
                break;
            lli aug = numeric_limits<lli>::max();
            for (int v = t; v != s; v = pv[v]) {
                int u = pv[v];
                Edge &e = g[u][pe[v]];
                if (e.cap < aug)
                    aug = e.cap;
            }
            for (int v = t; v != s; v = pv[v]) {
                int u = pv[v];
                int ei = pe[v];
                Edge &e = g[u][ei];
                e.cap -= aug;
                g[v][e.rev].cap += aug;
            }
            flow += aug;
        }
        return flow;
    }
};

bool skip(const string &line) {
    for (char ch : line) {
        if (isspace((unsigned char)ch))
            continue;
        return ch == 'c' || ch == '\0';
    }
    return true;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        cerr << "Missing dimacs file." << endl;
        return 1;
    }
    ifstream fin(argv[1]);
    if (!fin)
        return 1;

    int N = -1, M = -1, s = -1, t = -1;
    vector<tuple<int, int, lli>> edges;
    string line;

    while (getline(fin, line)) {
        if (skip(line))
            continue;
        istringstream iss(line);
        string tag;
        if (!(iss >> tag))
            continue;
        if (tag == "p") {
            string kind;
            iss >> kind >> N >> M;
        } else if (tag == "n") {
            int id;
            string which;
            iss >> id >> which;
            if (which == "s")
                s = id;
            else if (which == "t")
                t = id;
        } else if (tag == "a") {
            int u, v;
            lli c;
            iss >> u >> v >> c;
            edges.emplace_back(u, v, c);
        }
    }

    Graph G(N);
    for (auto &e : edges) {
        int u, v;
        lli c;
        tie(u, v, c) = e;
        G.add_edge(u - 1, v - 1, c);
    }
    cout << G.maxflow(s - 1, t - 1) << endl;
    return 0;
}
