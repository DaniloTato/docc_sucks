#include <iostream>

#include "algorithms.hpp"
#include "structs.hpp"

struct Input {
    size_t neighborhoods;
    WGraph dist_graph;
    WGraph flow_graph;
    vector<Point> exchanges;

    Input(std::istream &in) {
        size_t n;

        in >> n;

        neighborhoods = n;
        dist_graph = WGraph(n, in);
        flow_graph = WGraph(n, in);

        exchanges.reserve(n);
        for (size_t i = 0; i < n; i++)
            exchanges.emplace_back(in);
    }
};

int main() {
    Input input(std::cin);

    /*part 1*/
    vector<edge_t> mst_result = mst(input.dist_graph);
    for (edge_t e : mst_result)
        input.dist_graph.print_edge(std::cout, e);
    std::cout << "\n";

    /*part 2*/
    vector<node_t> tsp_result = tsp(input.dist_graph);
    for (node_t n : tsp_result)
        std::cout << n << " ";
    std::cout << "\n\n";

    /*part 3*/
    weight_t maxflow_result = maxflow(input.flow_graph);
    std::cout << maxflow_result << "\n\n";

    /*part 4*/
    vector<vector<Point>> voroni_cells_result = voroni_cells(input.exchanges);
    for (auto cell : voroni_cells_result) {
        for (Point p : cell)
            p.print(std::cout);
        std::cout << "\n";
    }

    return 0;
}
