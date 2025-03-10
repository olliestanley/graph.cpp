#ifndef DIGRAPH_H
#define DIGRAPH_H

#include "graph.h"

class DiGraph : public Graph {
public:
    DiGraph() : Graph() {}
    DiGraph(const AttrDict &attr) : Graph(attr) {}
    virtual ~DiGraph() {};

    void add_edge(const Node &u, const Node &v, const EdgeAttrMap &attr = {}) override;
    void remove_edge(const Node &u, const Node &v) override;
    bool has_edge(const Node &u, const Node &v) const override;

    double size(const std::string &weight = "") const override;

    bool is_directed() const override;
    bool is_multigraph() const override;

    Graph copy() const override;
    Graph to_directed(bool as_view = false) const override;
    Graph to_undirected(bool as_view = false) const override;
};

#endif
