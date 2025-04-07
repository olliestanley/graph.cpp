#include "multidigraph.h"
#include <stdexcept>
#include <sstream>
#include <algorithm>
#include <set>

using namespace std;

MultiDiGraph::MultiDiGraph() : DiGraph() {}
MultiDiGraph::MultiDiGraph(const AttrDict &attr) : DiGraph(attr) {}

void MultiDiGraph::add_edge(const Node &u, const Node &v, const EdgeAttrMap &attr) {
    if (!has_node(u)) add_node(u);
    if (!has_node(v)) add_node(v);

    int key = 0;
    if (_multi_adj[u][v].size() > 0) {
        key = 1 + max_element(
            _multi_adj[u][v].begin(), _multi_adj[u][v].end(),
            [](const auto &a, const auto &b) { return a.first < b.first; })->first;
    }

    _multi_adj[u][v][key] = attr;
}

void MultiDiGraph::remove_edge(const Node &u, const Node &v, int key) {
    if (!has_edge(u, v, key))
        throw runtime_error("The edge " + to_string(u) + "->" + to_string(v) + " with key " + to_string(key) + " is not in the graph.");

    _multi_adj[u][v].erase(key);
    if (_multi_adj[u][v].empty())
        _multi_adj[u].erase(v);
}

bool MultiDiGraph::has_edge(const Node &u, const Node &v, int key) const {
    auto it1 = _multi_adj.find(u);
    if (it1 == _multi_adj.end()) return false;
    auto it2 = it1->second.find(v);
    if (it2 == it1->second.end()) return false;
    return it2->second.find(key) != it2->second.end();
}

bool MultiDiGraph::has_edge(const Node &u, const Node &v) const {
    auto it1 = _multi_adj.find(u);
    return (it1 != _multi_adj.end() && it1->second.find(v) != it1->second.end());
}

vector<tuple<Graph::Node, Graph::Node, int>> MultiDiGraph::edges() const {
    vector<tuple<Node, Node, int>> edge_list;
    for (const auto &u_pair : _multi_adj) {
        Node u = u_pair.first;
        for (const auto &v_pair : u_pair.second) {
            Node v = v_pair.first;
            for (const auto &key_attr : v_pair.second) {
                int key = key_attr.first;
                edge_list.emplace_back(u, v, key);
            }
        }
    }
    return edge_list;
}

double MultiDiGraph::size(const string &weight) const {
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
    return s;
}

bool MultiDiGraph::is_multigraph() const {
    return true;
}

bool MultiDiGraph::is_directed() const {
    return true;
}

MultiDiGraph MultiDiGraph::copy() {
    MultiDiGraph G(graphAttributes);
    G._node = _node;
    G._multi_adj = _multi_adj;
    return G;
}

vector<Graph::Node> MultiDiGraph::neighbors(const Node &node) const {
    auto it = _multi_adj.find(node);
    if (it == _multi_adj.end())
        throw runtime_error("The node " + to_string(node) + " is not in the graph.");

    vector<Node> nbrs;
    for (const auto &pair : it->second)
        nbrs.push_back(pair.first);
    return nbrs;
}

map<Graph::Node, int> MultiDiGraph::degree() const {
    map<Node, int> deg;
    for (const auto &u_pair : _multi_adj) {
        Node u = u_pair.first;
        int count = 0;
        for (const auto &v_pair : u_pair.second) {
            count += v_pair.second.size();
        }
        deg[u] = count;
    }
    return deg;
}

void MultiDiGraph::clear_edges() {
    for (auto &pair : _multi_adj)
        pair.second.clear();
}

MultiGraph MultiDiGraph::to_undirected(bool as_view) {
    MultiGraph G(graphAttributes);
    G._node = _node;
    for (const auto &u_pair : _multi_adj) {
        Node u = u_pair.first;
        for (const auto &v_pair : u_pair.second) {
            Node v = v_pair.first;
            for (const auto &key_pair : v_pair.second) {
                int key = key_pair.first;
                G.add_edge(u, v, key_pair.second);
            }
        }
    }
    return G;
}
