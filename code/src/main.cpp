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

    // -------------------------------------------------------------
    // PART 1: MST – Fiber wiring plan
    // -------------------------------------------------------------
    std::cout << "END_OF_INPUT\n\n============================================================\n";
    std::cout << "1. Fiber Wiring Plan (Minimum Spanning Tree)\n";
    std::cout << "   List of arcs of the form (A, B):\n";
    std::cout << "------------------------------------------------------------\n";

    vector<edge_t> mst_result = mst(input.dist_graph);
    for (edge_t e : mst_result) {
        input.dist_graph.print_edge(std::cout, e);
        std::cout << "\n";
    }
    std::cout << "\n";

    // -------------------------------------------------------------
    // PART 2: TSP Route for Mail Delivery
    // -------------------------------------------------------------
    std::cout << "============================================================\n";
    std::cout << "2. Mail Delivery Route (TSP Approximation)\n";
    std::cout << "   Start and end in the same neighborhood:\n";
    std::cout << "------------------------------------------------------------\n";

    vector<node_t> tsp_result = tsp(input.dist_graph);
    for (node_t n : tsp_result)
        std::cout << n << " ";
    std::cout << "\n\n";

    // -------------------------------------------------------------
    // PART 3: Maximum Information Flow
    // -------------------------------------------------------------
    std::cout << "============================================================\n";
    std::cout << "3. Maximum Information Flow\n";
    std::cout << "   Value from the initial node to the final node:\n";
    std::cout << "------------------------------------------------------------\n";

    weight_t maxflow_result = maxflow(input.flow_graph);
    std::cout << maxflow_result << "\n\n";

    // -------------------------------------------------------------
    // PART 4: Voronoi Cells – Neighborhood Influence Zones
    // -------------------------------------------------------------
    std::cout << "============================================================\n";
    std::cout << "4. Voronoi Polygons for Exchange Centers\n";
    std::cout << "   Each polygon is a list of (x, y) points:\n";
    std::cout << "------------------------------------------------------------\n";

    vector<vector<Point>> voroni_cells_result = voroni_cells(input.exchanges);

    for (size_t i = 0; i < voroni_cells_result.size(); ++i) {
        std::cout << "Polygon " << i << ": ";
        for (const Point &p : voroni_cells_result[i]) {
            p.print(std::cout);
            std::cout << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\n============================================================\n";

    return 0;
}