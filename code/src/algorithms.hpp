#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "structs.hpp"

vector<edge_t> mst(const WGraph &graph);
vector<node_t> tsp(const WGraph &graph);
weight_t maxflow(const WGraph &graph);
vector<vector<Point>> voroni_cells(const vector<Point> &exchanges);

#endif // !ALGORITHMS_H
