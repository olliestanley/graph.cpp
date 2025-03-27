#include <iostream>
#include <stack>
#include <set>
#include <vector>
#include <stdexcept>
#include "graph.h"
#include "algorithms/dfs.h"
#include "utils/generator.h"

using namespace std;

vector<Graph::Node> dfs(const Graph &G, const Graph::Node &start) {
    if (!G.has_node(start))
        throw runtime_error("The start node is not in the graph.");

    vector<Graph::Node> visitOrder;
    set<Graph::Node> visited;
    stack<Graph::Node> s;
    s.push(start);

    while (!s.empty()) {
        Graph::Node current = s.top();
        s.pop();

        if (visited.find(current) != visited.end())
            continue;

        visited.insert(current);
        visitOrder.push_back(current);

        vector<Graph::Node> nbrs = G.neighbors(current);
        for (auto it = nbrs.rbegin(); it != nbrs.rend(); ++it) {
            if (visited.find(*it) == visited.end()) {
                s.push(*it);
            }
        }
    }

    return visitOrder;
}
