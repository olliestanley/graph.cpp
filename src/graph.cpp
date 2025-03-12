#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <stdexcept>
#include <sstream>
#include <tuple>
#include <cstdlib>
#include "graph.h"
#include "digraph.h"

using namespace std;

Graph::Graph() {}
Graph::Graph(const AttrDict &attr) : graphAttributes(attr) {}

string Graph::getName() const {
    auto it = graphAttributes.find("name");
    return (it != graphAttributes.end()) ? it->second : "";
}

void Graph::setName(const string &name) {
    graphAttributes["name"] = name;
}

string Graph::str() const {
    stringstream ss;
    ss << "Graph";
    if (!getName().empty())
        ss << " named '" << getName() << "'";
    ss << " with " << number_of_nodes() << " nodes and " << number_of_edges() << " edges";
    return ss.str();
}

void Graph::add_node(const Node &node, const AttrDict &attr) {
    if (_node.find(node) == _node.end()) {
        _node[node] = attr;
        _adj[node] = map<Node, EdgeAttrMap>();
    } else {
        for (const auto &p : attr)
            _node[node][p.first] = p.second;
    }
}

void Graph::add_nodes_from(const vector<Node> &nodes, const AttrDict &attr) {
    for (const auto &node : nodes)
        add_node(node, attr);
}

void Graph::add_nodes_from(const vector<pair<Node, AttrDict>> &nodes) {
    for (const auto &p : nodes)
        add_node(p.first, p.second);
}

void Graph::remove_node(const Node &node) {
    if (_node.find(node) == _node.end())
        throw runtime_error("The node " + to_string(node) + " is not in the graph.");
    auto neighbors = _adj[node];
    for (const auto &pair : neighbors) {
        Node nbr = pair.first;
        _adj[nbr].erase(node);
    }
    _node.erase(node);
    _adj.erase(node);
}

void Graph::remove_nodes_from(const vector<Node> &nodes) {
    for (const auto &node : nodes) {
        if (_node.find(node) != _node.end()) {
            auto neighbors = _adj[node];
            for (const auto &pair : neighbors)
                _adj[pair.first].erase(node);
            _node.erase(node);
            _adj.erase(node);
        }
    }
}

int Graph::number_of_nodes() const {
    return _node.size();
}

int Graph::order() const {
    return number_of_nodes();
}

bool Graph::has_node(const Node &node) const {
    return _node.find(node) != _node.end();
}

void Graph::add_edge(const Node &u, const Node &v, const EdgeAttrMap &attr) {
    if (!has_node(u)) add_node(u);
    if (!has_node(v)) add_node(v);

    EdgeAttrMap edgeData = attr;
    if (_adj[u].find(v) != _adj[u].end()) {
        for (const auto &p : attr)
            _adj[u][v][p.first] = p.second;
    } else {
        _adj[u][v] = edgeData;
    }
    if (_adj[v].find(u) != _adj[v].end()) {
        for (const auto &p : attr)
            _adj[v][u][p.first] = p.second;
    } else {
        _adj[v][u] = edgeData;
    }
}

void Graph::add_edges_from(const vector<pair<Node, Node>> &edges, const EdgeAttrMap &attr) {
    for (const auto &edge : edges)
        add_edge(edge.first, edge.second, attr);
}

void Graph::add_edges_from(const vector<tuple<Node, Node, EdgeAttrMap>> &edges) {
    for (const auto &edge : edges) {
        Node u, v;
        EdgeAttrMap edata;
        tie(u, v, edata) = edge;
        add_edge(u, v, edata);
    }
}

void Graph::remove_edge(const Node &u, const Node &v) {
    if (_adj.find(u) == _adj.end() || _adj[u].find(v) == _adj[u].end())
        throw runtime_error("The edge " + to_string(u) + "-" + to_string(v) + " is not in the graph.");
    _adj[u].erase(v);
    if (u != v)
        _adj[v].erase(u);
}

void Graph::remove_edges_from(const vector<pair<Node, Node>> &edges) {
    for (const auto &edge : edges) {
        Node u = edge.first, v = edge.second;
        if (_adj.find(u) != _adj.end() && _adj[u].find(v) != _adj[u].end()) {
            _adj[u].erase(v);
            if (u != v)
                _adj[v].erase(u);
        }
    }
}

bool Graph::has_edge(const Node &u, const Node &v) const {
    auto it = _adj.find(u);
    return (it != _adj.end() && it->second.find(v) != it->second.end());
}

vector<Graph::Node> Graph::neighbors(const Node &node) const {
    if (_adj.find(node) == _adj.end())
        throw runtime_error("The node " + to_string(node) + " is not in the graph.");
    vector<Node> nbrs;
    for (const auto &pair : _adj.at(node))
        nbrs.push_back(pair.first);
    return nbrs;
}

double Graph::size(const string &weight) const {
    double s = 0;
    if (weight.empty()) {
        for (const auto &pair : _adj)
            s += pair.second.size();
        return s / 2;
    } else {
        for (const auto &u_pair : _adj) {
            for (const auto &v_pair : u_pair.second) {
                auto it = v_pair.second.find(weight);
                if (it != v_pair.second.end())
                    s += stod(it->second);
            }
        }
        return s / 2;
    }
}

int Graph::number_of_edges() const {
    return static_cast<int>(size());
}

map<Graph::Node, int> Graph::degree() const {
    map<Node, int> deg;
    for (const auto &pair : _adj)
        deg[pair.first] = pair.second.size();
    return deg;
}

void Graph::clear() {
    _node.clear();
    _adj.clear();
    graphAttributes.clear();
}

void Graph::clear_edges() {
    for (auto &pair : _adj)
        pair.second.clear();
}

bool Graph::is_multigraph() const {
    return false;
}

bool Graph::is_directed() const {
    return false;
}

Graph Graph::copy() const {
    Graph G;
    G.graphAttributes = graphAttributes;
    G._node = _node;
    G._adj = _adj;
    return G;
}

Graph Graph::to_directed(bool as_view) const {
    DiGraph D(graphAttributes);
    for (const auto &nodePair : _node) {
        D.add_node(nodePair.first, nodePair.second);
    }
    for (const auto &u_pair : _adj) {
        for (const auto &v_pair : u_pair.second) {
            D.add_edge(u_pair.first, v_pair.first, v_pair.second);
        }
    }
    return D;
}

Graph Graph::to_undirected(bool as_view) const {
    return copy();
}

Graph Graph::subgraph(const vector<Node> &nodes) const {
    Graph subG;
    set<Node> nodeSet(nodes.begin(), nodes.end());
    for (const auto &p : _node) {
        if (nodeSet.find(p.first) != nodeSet.end())
            subG.add_node(p.first, p.second);
    }
    for (const auto &u_pair : _adj) {
        Node u = u_pair.first;
        if (nodeSet.find(u) != nodeSet.end()) {
            for (const auto &v_pair : u_pair.second) {
                Node v = v_pair.first;
                if (nodeSet.find(v) != nodeSet.end())
                    subG.add_edge(u, v, v_pair.second);
            }
        }
    }
    return subG;
}

Graph Graph::edge_subgraph(const vector<pair<Node, Node>> &edges) const {
    Graph subG;
    for (const auto &edge : edges) {
        Node u = edge.first, v = edge.second;
        if (has_edge(u, v)) {
            subG.add_node(u, _node.at(u));
            subG.add_node(v, _node.at(v));
            subG.add_edge(u, v, _adj.at(u).at(v));
        }
    }
    return subG;
}

ostream &operator<<(ostream &os, const Graph &G) {
    os << G.str();
    return os;
}
