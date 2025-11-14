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

    std::cout << "part 1:\n\n";
    vector<edge_t> mst_result = mst(input.dist_graph);
    for (edge_t e : mst_result)
        input.dist_graph.print_edge(std::cout, e);
    std::cout << "\n";

    std::cout << "part 2:\n\n";
    vector<node_t> tsp_result = tsp(input.dist_graph);
    for (node_t n : tsp_result)
        std::cout << n << " ";
    std::cout << "\n\n";

    std::cout << "part 3:\n\n";
    weight_t maxflow_result = maxflow(input.flow_graph);
    std::cout << maxflow_result << "\n\n";

    std::cout << "part 4:\n\n";
    vector<vector<Point>> voroni_cells_result = voroni_cells(input.exchanges);
    for (auto cell : voroni_cells_result) {
        for (Point p : cell)
            p.print(std::cout);
        std::cout << "\n";
    }

    return 0;
}
