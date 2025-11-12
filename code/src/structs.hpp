#ifndef STRUCTS_H
#define STRUCTS_H

#include <complex>
#include <istream>
#include <ostream>
#include <vector>

using std::vector;

typedef int node_t;
typedef int weight_t;
typedef std::pair<node_t, node_t> edge_t;

struct WGraph {
    size_t n;
    vector<vector<weight_t>> mat;

    WGraph();
    WGraph(size_t n, std::istream &in);

    void print_edge(std::ostream &out, edge_t edge);
};

struct Point {
    using ptype = int;
    std::complex<ptype> val;

    Point();
    Point(std::istream &in);

    void print(std::ostream &out);
};

template <typename T> void print_pair(std::ostream &out, T a, T b);

#endif // !STRUCTS_H
