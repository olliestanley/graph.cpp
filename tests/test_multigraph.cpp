#include "multigraph.h"
#include "multidigraph.h"
#include <gtest/gtest.h>

TEST(MultiGraphTest, AddMultipleEdges) {
    MultiGraph g;
    g.add_edge(1, 2, {{"weight", "1.0"}});
    g.add_edge(1, 2, {{"weight", "2.0"}});

    EXPECT_TRUE(g.has_edge(1, 2));
    EXPECT_EQ(static_cast<int>(g.size()), 2);
}

TEST(MultiGraphTest, RemoveEdgeWithKey) {
    MultiGraph g;
    g.add_edge(1, 2, {{"label", "a"}});
    g.add_edge(1, 2, {{"label", "b"}});

    auto all_edges = g.edges();
    ASSERT_EQ(all_edges.size(), 2);

    int key_to_remove = std::get<2>(all_edges[0]);
    g.remove_edge(1, 2, key_to_remove);

    EXPECT_EQ(static_cast<int>(g.size()), 1);
    EXPECT_TRUE(g.has_edge(1, 2));
}

TEST(MultiGraphTest, EdgeAttributesDiffer) {
    MultiGraph g;
    g.add_edge(1, 2, {{"label", "x"}});
    g.add_edge(1, 2, {{"label", "y"}});

    auto edges = g.edges();
    std::set<std::string> labels;
    for (const auto& [u, v, k] : edges) {
        auto attr = g._multi_adj[u][v][k];
        labels.insert(attr.at("label"));
    }

    EXPECT_EQ(labels.size(), 2);
    EXPECT_TRUE(labels.count("x"));
    EXPECT_TRUE(labels.count("y"));
}

TEST(MultiGraphTest, CopyPreservesEdges) {
    MultiGraph g;
    g.add_edge(1, 2);
    g.add_edge(1, 2);
    g.add_edge(2, 3);

    MultiGraph g2 = g.copy();

    EXPECT_EQ(static_cast<int>(g2.size()), 3);
    EXPECT_TRUE(g2.has_edge(1, 2));
    EXPECT_TRUE(g2.has_edge(2, 3));
    EXPECT_EQ(g2.edges().size(), 3);
}

TEST(MultiGraphTest, IsMultigraph) {
    MultiGraph g;
    EXPECT_TRUE(g.is_multigraph());
}

TEST(MultiGraphTest, NeighborsAreCorrect) {
    MultiGraph g;
    g.add_edge(1, 2);
    g.add_edge(1, 3);
    g.add_edge(1, 2);

    auto nbrs = g.neighbors(1);
    std::set<int> nbr_set(nbrs.begin(), nbrs.end());

    EXPECT_EQ(nbr_set.size(), 2);
    EXPECT_TRUE(nbr_set.count(2));
    EXPECT_TRUE(nbr_set.count(3));
}

TEST(MultiGraphTest, DegreeCountsMultiEdges) {
    MultiGraph g;
    g.add_edge(1, 2);
    g.add_edge(1, 2);
    g.add_edge(1, 3);

    auto deg = g.degree();

    EXPECT_EQ(deg[1], 3);  // Two to 2, one to 3
    EXPECT_EQ(deg[2], 2);  // Two from 1
    EXPECT_EQ(deg[3], 1);  // One from 1
}

TEST(MultiGraphTest, ClearEdgesRemovesAllButPreservesNodes) {
    MultiGraph g;
    g.add_node(1, {{"color", "red"}});
    g.add_node(2);
    g.add_edge(1, 2);
    g.add_edge(1, 2);

    g.clear_edges();

    EXPECT_EQ(static_cast<int>(g.size()), 0);
    EXPECT_TRUE(g.has_node(1));
    EXPECT_EQ(g._node.at(1).at("color"), "red");
    EXPECT_TRUE(g.has_node(2));
}

TEST(MultiGraphTest, ToDirectedCreatesSymmetricMultiDiGraph) {
    MultiGraph g;
    g.add_edge(1, 2, {{"w", "x"}});
    g.add_edge(1, 2, {{"w", "y"}});

    MultiDiGraph directed = g.to_directed();
    EXPECT_TRUE(directed.is_directed());
    EXPECT_TRUE(directed.is_multigraph());

    int count12 = 0, count21 = 0;
    for (const auto& [u, v, k] : directed.edges()) {
        if (u == 1 && v == 2) count12++;
        if (u == 2 && v == 1) count21++;
    }

    EXPECT_EQ(count12, 2);
    EXPECT_EQ(count21, 2);
}
