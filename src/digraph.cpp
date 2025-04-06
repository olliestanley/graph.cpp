#include "digraph.h"

using namespace std;

DiGraph::DiGraph() : Graph() {}
DiGraph::DiGraph(const AttrDict &attr) : Graph(attr) {}

void DiGraph::add_edge(const Node &u, const Node &v, const EdgeAttrMap &attr) {
    if (!has_node(u)) add_node(u);
    if (!has_node(v)) add_node(v);

    _adj[u][v] = attr;
}

void DiGraph::remove_edge(const Node &u, const Node &v) {
    if (_adj.find(u) == _adj.end() || _adj[u].find(v) == _adj[u].end())
        throw runtime_error("The edge " + to_string(u) + "->" + to_string(v) + " is not in the graph.");
    _adj[u].erase(v);
}

bool DiGraph::has_edge(const Node &u, const Node &v) const {
    auto it = _adj.find(u);
    return (it != _adj.end() && it->second.find(v) != it->second.end());
}

double DiGraph::size(const string &weight) const {
    double s = 0;
    if (weight.empty()) {
        for (const auto &pair : _adj)
            s += pair.second.size();
        return s;
    } else {
        for (const auto &u_pair : _adj) {
            for (const auto &v_pair : u_pair.second) {
                auto it = v_pair.second.find(weight);
                if (it != v_pair.second.end())
                    s += stod(it->second);
            }
        }
        return s;
    }
}

bool DiGraph::is_directed() const {
    return true;
}

bool DiGraph::is_multigraph() const {
    return false;
}

DiGraph DiGraph::copy() {
    DiGraph G(graphAttributes);
    G._node = _node;
    G._adj = _adj;
    return G;
}

DiGraph DiGraph::to_directed(bool as_view) {
    return copy();
}

Graph DiGraph::to_undirected(bool as_view) const {
    Graph G;
    G.graphAttributes = graphAttributes;
    G._node = _node;
    for (const auto &u_pair : _adj) {
        Node u = u_pair.first;
        for (const auto &v_pair : u_pair.second) {
            Node v = v_pair.first;
            G.add_edge(u, v, v_pair.second);
            G.add_edge(v, u, v_pair.second);
        }
    }
    return G;
}
