#include "structs.hpp"
#include <ostream>

WGraph::WGraph() : n(0) {}
WGraph::WGraph(size_t n, std::istream &in) : n(n) {
    mat = vector<vector<weight_t>>(n, vector<weight_t>(n, 0));
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            in >> mat[i][j];
        }
    }
}
void WGraph::print_edge(std::ostream &out, edge_t edge) {
    print_pair(out, edge.first, edge.second);
}

Point::Point() : val(0, 0) {}
Point::Point(std::istream &in) {
    char discard;
    ptype real, imag;
    in >> discard >> real >> discard >> imag >> discard;
    val = {real, imag};
}
void Point::print(std::ostream &out) {
    print_pair(out, val.real(), val.imag());
}

template <typename T> void print_pair(std::ostream &out, T a, T b) {
    out << "(" << a << "," << b << ")\n";
}
