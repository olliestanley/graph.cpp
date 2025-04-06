#ifndef MULTIGRAPH_H
#define MULTIGRAPH_H

#include "graph.h"

class MultiGraph : public Graph {
public:
    using EdgeKey = int;
    using MultiEdgeAttrMap = std::map<EdgeKey, EdgeAttrMap>;
    using MultiAdjList = std::map<Node, std::map<Node, MultiEdgeAttrMap>>;

public:
    MultiAdjList _multi_adj;

public:
    MultiGraph();
    MultiGraph(const AttrDict &attr);

    void add_edge(const Node &u, const Node &v, const EdgeAttrMap &attr = {}) override;
    void remove_edge(const Node &u, const Node &v, int key);
    bool has_edge(const Node &u, const Node &v, int key) const;
    bool has_edge(const Node &u, const Node &v) const override;
    std::vector<std::tuple<Node, Node, int>> edges() const;

    double size(const std::string &weight = "") const override;
    bool is_multigraph() const override;

    MultiGraph copy();
};

#endif
