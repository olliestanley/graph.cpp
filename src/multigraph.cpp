#include "multigraph.h"
#include <stdexcept>
#include <sstream>
#include <algorithm>

using namespace std;

MultiGraph::MultiGraph() : Graph() {}
MultiGraph::MultiGraph(const AttrDict &attr) : Graph(attr) {}

void MultiGraph::add_edge(const Node &u, const Node &v, const EdgeAttrMap &attr) {
    if (!has_node(u)) add_node(u);
    if (!has_node(v)) add_node(v);

    int key = 0;
    if (_multi_adj[u][v].size() > 0) {
        key = 1 + max_element(
            _multi_adj[u][v].begin(), _multi_adj[u][v].end(),
            [](const auto &a, const auto &b) { return a.first < b.first; })->first;
    }

    _multi_adj[u][v][key] = attr;
    if (u != v)
        _multi_adj[v][u][key] = attr;
}

void MultiGraph::remove_edge(const Node &u, const Node &v, int key) {
    if (!has_edge(u, v, key))
        throw runtime_error("The edge " + to_string(u) + "-" + to_string(v) + " with key " + to_string(key) + " is not in the graph.");

    _multi_adj[u][v].erase(key);
    if (_multi_adj[u][v].empty())
        _multi_adj[u].erase(v);

    if (u != v) {
        _multi_adj[v][u].erase(key);
        if (_multi_adj[v][u].empty())
            _multi_adj[v].erase(u);
    }
}

bool MultiGraph::has_edge(const Node &u, const Node &v) const {
    auto it1 = _multi_adj.find(u);
    if (it1 == _multi_adj.end()) return false;
    return it1->second.find(v) != it1->second.end();
}

bool MultiGraph::has_edge(const Node &u, const Node &v, int key) const {
    auto it1 = _multi_adj.find(u);
    if (it1 == _multi_adj.end()) return false;
    auto it2 = it1->second.find(v);
    if (it2 == it1->second.end()) return false;
    return it2->second.find(key) != it2->second.end();
}

vector<tuple<Graph::Node, Graph::Node, int>> MultiGraph::edges() const {
    set<tuple<Node, Node, int>> edge_set;
    for (const auto &u_pair : _multi_adj) {
        Node u = u_pair.first;
        for (const auto &v_pair : u_pair.second) {
            Node v = v_pair.first;
            for (const auto &key_attr : v_pair.second) {
                int key = key_attr.first;
                if (u <= v)
                    edge_set.emplace(u, v, key);
                else
                    edge_set.emplace(v, u, key);
            }
        }
    }
    return vector<tuple<Node, Node, int>>(edge_set.begin(), edge_set.end());
}

double MultiGraph::size(const string &weight) const {
    double s = 0;
    for (const auto &u_pair : _multi_adj) {
        for (const auto &v_pair : u_pair.second) {
            for (const auto &key_pair : v_pair.second) {
                if (weight.empty()) {
                    s += 1;
                } else {
                    auto it = key_pair.second.find(weight);
                    if (it != key_pair.second.end())
                        s += stod(it->second);
                }
            }
        }
    }
    return s / 2;
}

bool MultiGraph::is_multigraph() const {
    return true;
}

MultiGraph MultiGraph::copy() {
    MultiGraph G(graphAttributes);
    G._node = _node;
    G._multi_adj = _multi_adj;
    return G;
}
