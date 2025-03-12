#include <iostream>
#include <queue>
#include <set>
#include <vector>
#include <stdexcept>
#include "graph.h"
#include "algorithms/bfs.h"

using namespace std;

vector<Graph::Node> bfs(const Graph &G, const Graph::Node &start) {
    if (!G.has_node(start))
        throw runtime_error("The start node is not in the graph.");

    vector<Graph::Node> visitOrder;
    set<Graph::Node> visited;
    queue<Graph::Node> q;

    visited.insert(start);
    q.push(start);

    while (!q.empty()) {
        Graph::Node current = q.front();
        q.pop();
        visitOrder.push_back(current);

        vector<Graph::Node> nbrs = G.neighbors(current);
        for (const auto &nbr : nbrs) {
            if (visited.find(nbr) == visited.end()) {
                visited.insert(nbr);
                q.push(nbr);
            }
        }
    }
    return visitOrder;
}
