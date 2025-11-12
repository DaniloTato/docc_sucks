// algorithms.cpp
#include "algorithms.hpp"
#include <algorithm>
#include <cmath>
#include <limits>
#include <queue>

// -------------------- MST (Kruskal) --------------------
struct DSU {
    vector<int> p, r;
    DSU(int n = 0) : p(n), r(n, 0) {
        for (int i = 0; i < n; ++i)
            p[i] = i;
    }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b)
            return false;
        if (r[a] < r[b])
            std::swap(a, b);
        p[b] = a;
        if (r[a] == r[b])
            ++r[a];
        return true;
    }
};

vector<edge_t> mst(const WGraph &g) {
    struct E {
        int u, v;
        weight_t w;
    };
    vector<E> edges;
    for (int i = 0; i < (int)g.n; ++i)
        for (int j = i + 1; j < (int)g.n; ++j)
            if (g.mat[i][j] > 0)
                edges.push_back({i, j, g.mat[i][j]});
    std::sort(edges.begin(), edges.end(),
              [](const E &a, const E &b) { return a.w < b.w; });

    DSU dsu((int)g.n);
    vector<edge_t> tree;
    tree.reserve(g.n ? g.n - 1 : 0);
    for (auto &e : edges) {
        if (dsu.unite(e.u, e.v)) {
            tree.emplace_back(e.u, e.v);
            if (tree.size() + 1 == g.n)
                break;
        }
    }
    return tree; // if graph disconnected, this is a forest
}

// -------------------- TSP (Nearest Neighbor tour from 0) --------------------
vector<node_t> tsp(const WGraph &g) {
    int n = (int)g.n;
    if (n == 0)
        return {};
    vector<char> vis(n, false);
    vector<node_t> tour;
    tour.reserve(n + 1);
    int cur = 0;
    vis[cur] = true;
    tour.push_back(cur);
    for (int step = 1; step < n; ++step) {
        int nxt = -1;
        weight_t best = std::numeric_limits<weight_t>::max();
        for (int v = 0; v < n; ++v)
            if (!vis[v] && g.mat[cur][v] > 0 && g.mat[cur][v] < best) {
                best = g.mat[cur][v];
                nxt = v;
            }
        if (nxt == -1) {
            // fallback: pick any unvisited (disconnected case)
            for (int v = 0; v < n; ++v)
                if (!vis[v]) {
                    nxt = v;
                    break;
                }
        }
        vis[nxt] = true;
        tour.push_back(nxt);
        cur = nxt;
    }
    tour.push_back(0); // close the cycle
    return tour;
}

// -------------------- Max Flow (Edmonds–Karp 0 -> n-1) --------------------
weight_t maxflow(const WGraph &g) {
    int n = (int)g.n;
    if (n == 0)
        return 0;
    int s = 0, t = n - 1;
    // use long long internally to avoid overflow, return weight_t at the end
    vector<vector<long long>> cap(n, vector<long long>(n, 0));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cap[i][j] = g.mat[i][j];

    long long flow = 0;
    while (true) {
        vector<int> par(n, -1);
        par[s] = -2;
        vector<long long> add(n, 0);
        add[s] = std::numeric_limits<long long>::max();
        std::queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v = 0; v < n; ++v)
                if (par[v] == -1 && cap[u][v] > 0) {
                    par[v] = u;
                    add[v] = std::min(add[u], cap[u][v]);
                    if (v == t)
                        break;
                    q.push(v);
                }
            if (par[t] != -1)
                break;
        }
        if (par[t] == -1)
            break; // no augmenting path
        long long aug = add[t];
        flow += aug;
        for (int v = t; v != s; v = par[v]) {
            int u = par[v];
            cap[u][v] -= aug;
            cap[v][u] += aug;
        }
    }
    // clamp to weight_t if needed
    return (weight_t)flow;
}

// -------------------- Voronoi via half-plane clipping --------------------
namespace detail {
struct DPt {
    double x, y;
};
static inline double dot(const DPt &a, const DPt &b) {
    return a.x * b.x + a.y * b.y;
}
static inline DPt sub(const DPt &a, const DPt &b) {
    return {a.x - b.x, a.y - b.y};
}

// Signed distance difference to decide which side is closer to site A than B
// Keep points P where |P-A|^2 <= |P-B|^2  => (P·P cancels)
static inline double sideVal(const DPt &P, const DPt &A, const DPt &B) {
    // Equivalent to (B-A)·(B+A-2P) >= 0, but use simpler form:
    // Keep P with (P·(B-A)) <= 0.5*(B·B - A·A)
    DPt BA = sub(B, A);
    return dot(P, BA) - 0.5 * (dot(B, B) - dot(A, A));
}

// Segment intersection with the bisector line L: sideVal == 0
static bool intersectOnBisector(const DPt &P, const DPt &Q, const DPt &A,
                                const DPt &B, DPt &out) {
    double sP = sideVal(P, A, B), sQ = sideVal(Q, A, B);
    double d = sP - sQ;
    if (std::fabs(d) < 1e-12)
        return false;          // parallel to the line in numeric sense
    double t = sP / (sP - sQ); // intersection along PQ
    if (t < -1e-12 || t > 1 + 1e-12)
        return false;
    out = {P.x + t * (Q.x - P.x), P.y + t * (Q.y - P.y)};
    return true;
}

// Clip polygon poly against half-plane: keep side closer to A than to B.
static vector<DPt> clipHalfPlane(const vector<DPt> &poly, const DPt &A,
                                 const DPt &B) {
    vector<DPt> out;
    int m = (int)poly.size();
    if (m == 0)
        return out;
    for (int i = 0; i < m; ++i) {
        DPt P = poly[i], Q = poly[(i + 1) % m];
        double sP = sideVal(P, A, B), sQ = sideVal(Q, A, B);
        bool inP = sP <= 1e-12,
             inQ = sQ <= 1e-12; // keep "closer-or-equal" side
        if (inP && inQ) {
            out.push_back(Q);
        } else if (inP && !inQ) {
            DPt I;
            if (intersectOnBisector(P, Q, A, B, I))
                out.push_back(I);
        } else if (!inP && inQ) {
            DPt I;
            if (intersectOnBisector(P, Q, A, B, I))
                out.push_back(I);
            out.push_back(Q);
        } // else both out: add nothing
    }
    return out;
}
} // namespace detail

vector<vector<Point>> voroni_cells(const vector<Point> &ex) {
    using namespace detail;
    const int m = (int)ex.size();
    vector<DPt> S(m);
    for (int i = 0; i < m; ++i) {
        S[i] = {(double)ex[i].val.real(), (double)ex[i].val.imag()};
    }
    if (m == 0)
        return {};

    // Compute a bounding box and expand it
    double minx = S[0].x, maxx = S[0].x, miny = S[0].y, maxy = S[0].y;
    for (auto &p : S) {
        minx = std::min(minx, p.x);
        maxx = std::max(maxx, p.x);
        miny = std::min(miny, p.y);
        maxy = std::max(maxy, p.y);
    }
    double dx = std::max(10.0, (maxx - minx) * 0.5 + 5.0);
    double dy = std::max(10.0, (maxy - miny) * 0.5 + 5.0);
    minx -= dx;
    maxx += dx;
    miny -= dy;
    maxy += dy;

    const vector<DPt> bbox = {
        {minx, miny}, {maxx, miny}, {maxx, maxy}, {minx, maxy}};

    vector<vector<Point>> cells(m);

    for (int i = 0; i < m; ++i) {
        // Start with the bbox polygon, iteratively clip by all bisectors vs
        // other sites
        vector<DPt> poly = bbox;
        for (int j = 0; j < m; ++j)
            if (i != j) {
                poly = clipHalfPlane(poly, S[i], S[j]);
                if (poly.empty())
                    break;
            }
        // Round vertices to integers for Point (ptype=int)
        vector<Point> cell;
        cell.reserve(poly.size());
        for (auto &q : poly) {
            Point::ptype xi = (Point::ptype)std::llround(q.x);
            Point::ptype yi = (Point::ptype)std::llround(q.y);
            Point pt;
            pt.val = {xi, yi};
            cell.push_back(pt);
        }
        cells[i] = std::move(cell);
    }
    return cells;
}
