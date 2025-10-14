#include "tsp_algorithms.hpp"
#include <climits>
#include <functional>
#include <algorithm>

using ll = long long;

//NEAREST NEIGHBOR
/*
Description:
Greedy heuristic that builds a tour by repeatedly 
visiting the nearest unvisited city.

Time Complexity: O(n^2)
- For each of the n cities, we search among all others 
    for the nearest unvisited one is O(n) per step.
- Total: n * O(n) = O(n^2)
Space Complexity: O(n)
- Stores visited flags and the resulting tour.
*/
std::pair<ll, std::vector<int>> nearest_neighbor(const std::vector<std::vector<ll>>& d, int start_idx) {
    int n = d.size();
    std::vector<char> used(n, false);
    std::vector<int> tour; tour.reserve(n + 1);
    int cur = start_idx;
    tour.push_back(cur);
    used[cur] = true;
    ll cost = 0;

    for (int step = 1; step < n; ++step) {
        int best = -1; ll bestd = LLONG_MAX;
        for (int j = 0; j < n; j++) if (!used[j] && d[cur][j] < bestd) {
            bestd = d[cur][j]; best = j;
        }
        tour.push_back(best);
        used[best] = true;
        cost += bestd;
        cur = best;
    }

    cost += d[cur][tour[0]];
    tour.push_back(tour[0]);
    return {cost, tour};
}

//MINIMUM SPANNING TREE TSP
/*
Description:
Uses Prim’s algorithm to build an MST, then performs
a preorder DFS traversal to generate an approximate TSP tour.
    
Time Complexity: O(n^2)
- Prim’s algorithm on a dense adjacency matrix: O(n^2)
- DFS traversal: O(n)
- Total: O(n^2)
Space Complexity: O(n)
- Stores parent, key, adjacency, and visited arrays.
*/
std::pair<ll, std::vector<int>> mst_tsp(const std::vector<std::vector<ll>>& d) {
    int n = d.size();
    std::vector<ll> key(n, LLONG_MAX);
    std::vector<int> parent(n, -1);
    std::vector<char> inMST(n, false);
    key[0] = 0;

    for (int i = 0; i < n; i++) {
        int u = -1; ll best = LLONG_MAX;
        for (int v = 0; v < n; v++)
            if (!inMST[v] && key[v] < best) { best = key[v]; u = v; }

        if (u == -1) break;
        inMST[u] = true;

        for (int v = 0; v < n; v++)
            if (!inMST[v] && d[u][v] < key[v]) { key[v] = d[u][v]; parent[v] = u; }
    }

    std::vector<std::vector<int>> adj(n);
    for (int v = 1; v < n; ++v) {
        if (parent[v] >= 0) {
            adj[v].push_back(parent[v]);
            adj[parent[v]].push_back(v);
        }
    }

    std::vector<int> tour_nodes;
    std::vector<char> visited(n, false);
    std::function<void(int)> dfs = [&](int u) {
        visited[u] = true;
        tour_nodes.push_back(u);
        for (int w : adj[u]) if (!visited[w]) dfs(w);
    };
    dfs(0);

    ll cost = 0;
    for (int i = 0; i + 1 < n; i++) cost += d[tour_nodes[i]][tour_nodes[i + 1]];
    cost += d[tour_nodes.back()][tour_nodes.front()];
    tour_nodes.push_back(tour_nodes.front());
    return {cost, tour_nodes};
}

//CHEAPEST LINK
/*
Description:
Kruskal-like greedy heuristic:
    1. Sorts all edges by weight.
    2. Adds edges if they don't form a premature cycle 
        and no vertex exceeds degree 2.
    3. Closes the cycle at the end.

Time Complexity: O(n^2 log n)
- Complete graph has O(n^2) edges.
- Sorting edges: O(n^2 log n)
- DSU union/find and degree checks: O(n^2)
- Total dominated by sorting step: O(n^2 log n)
Space Complexity: O(n^2)
- Stores all edges explicitly.
*/
struct DSU {
    std::vector<int> p;
    DSU(int n=0):p(n,-1){}
    int find(int a){ return p[a]<0? a : p[a]=find(p[a]); }
    bool unite(int a,int b){
        a=find(a); b=find(b);
        if(a==b) return false;
        if(p[a]>p[b]) std::swap(a,b);
        p[a]+=p[b]; p[b]=a;
        return true;
    }
};

std::pair<ll, std::vector<int>> cheapest_link(const std::vector<std::vector<ll>>& d) {
    int n = d.size();
    struct Edge{int u,v; ll w;};
    std::vector<Edge> edges;
    for (int i=0;i<n;i++)
        for (int j=i+1;j<n;j++)
            edges.push_back({i,j,d[i][j]});
    std::sort(edges.begin(), edges.end(), [](auto &a, auto &b){ return a.w<b.w; });

    std::vector<int> deg(n,0);
    DSU dsu(n);
    std::vector<std::vector<int>> adj(n);
    for (auto &e : edges) {
        if (deg[e.u] >= 2 || deg[e.v] >= 2) continue;
        if (dsu.find(e.u) == dsu.find(e.v)) continue;
        deg[e.u]++; deg[e.v]++;
        dsu.unite(e.u, e.v);
        adj[e.u].push_back(e.v);
        adj[e.v].push_back(e.u);
    }

    for (auto &e : edges)
        if (deg[e.u]==1 && deg[e.v]==1) {
            adj[e.u].push_back(e.v);
            adj[e.v].push_back(e.u);
            break;
        }

    std::vector<int> tour;
    int cur = 0, prev = -1;
    for (int i=0;i<n;i++) {
        tour.push_back(cur);
        int next = (adj[cur][0]==prev)? adj[cur][1] : adj[cur][0];
        prev = cur;
        cur = next;
    }
    tour.push_back(tour.front());

    ll cost=0;
    for (int i=0;i+1<(int)tour.size();++i) cost+=d[tour[i]][tour[i+1]];
    return {cost,tour};
}