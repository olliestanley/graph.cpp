#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <stdexcept>
#include <sstream>
#include <tuple>

class Graph {
public:
    using Node = int;
    using AttrDict = std::map<std::string, std::string>;
    using NodeAttrMap = std::map<Node, AttrDict>;
    using EdgeAttrMap = std::map<std::string, std::string>;
    using AdjList = std::map<Node, std::map<Node, EdgeAttrMap>>;

    std::map<std::string, std::string> graphAttributes;

    NodeAttrMap _node;
    AdjList _adj;

public:
    Graph();
    Graph(const AttrDict &attr);
    virtual ~Graph() = default;

    std::string getName() const;
    void setName(const std::string &name);

    std::string str() const;

    void add_node(const Node &node, const AttrDict &attr = {});
    void add_nodes_from(const std::vector<Node> &nodes, const AttrDict &attr = {});
    void add_nodes_from(const std::vector<std::pair<Node, AttrDict>> &nodes);
    void remove_node(const Node &node);
    void remove_nodes_from(const std::vector<Node> &nodes);
    int number_of_nodes() const;
    int order() const;
    bool has_node(const Node &node) const;

    virtual void add_edge(const Node &u, const Node &v, const EdgeAttrMap &attr = {});
    void add_edges_from(const std::vector<std::pair<Node, Node>> &edges, const EdgeAttrMap &attr = {});
    void add_edges_from(const std::vector<std::tuple<Node, Node, EdgeAttrMap>> &edges);
    virtual void remove_edge(const Node &u, const Node &v);
    void remove_edges_from(const std::vector<std::pair<Node, Node>> &edges);
    virtual bool has_edge(const Node &u, const Node &v) const;

    std::vector<Node> neighbors(const Node &node) const;

    int number_of_edges() const;
    std::map<Node, int> degree() const;

    virtual double size(const std::string &weight = "") const;

    void clear();
    void clear_edges();

    virtual bool is_multigraph() const;
    virtual bool is_directed() const;

    virtual Graph copy() const;
    virtual Graph to_directed(bool as_view = false) const;
    virtual Graph to_undirected(bool as_view = false) const;

    Graph subgraph(const std::vector<Node> &nodes) const;
    Graph edge_subgraph(const std::vector<std::pair<Node, Node>> &edges) const;
};

std::ostream &operator<<(std::ostream &os, const Graph &G);

#endif
