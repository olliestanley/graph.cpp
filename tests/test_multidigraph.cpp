#include "multidigraph.h"
#include <gtest/gtest.h>

TEST(MultiDiGraphTest, AddMultipleEdges) {
    MultiDiGraph g;
    g.add_edge(1, 2, {{"weight", "1.0"}});
    g.add_edge(1, 2, {{"weight", "2.0"}});

    EXPECT_TRUE(g.has_edge(1, 2));
    EXPECT_EQ(static_cast<int>(g.size()), 2);
}

TEST(MultiDiGraphTest, RemoveEdgeWithKey) {
    MultiDiGraph g;
    g.add_edge(1, 2, {{"label", "a"}});
    g.add_edge(1, 2, {{"label", "b"}});

    auto edges = g.edges();
    ASSERT_EQ(edges.size(), 2);
    int key = std::get<2>(edges[0]);

    g.remove_edge(1, 2, key);
    EXPECT_EQ(static_cast<int>(g.size()), 1);
    EXPECT_TRUE(g.has_edge(1, 2));
}

TEST(MultiDiGraphTest, HasEdgeWithKey) {
    MultiDiGraph g;
    g.add_edge(1, 2);
    g.add_edge(1, 2);

    auto edges = g.edges();
    ASSERT_EQ(edges.size(), 2);
    int key0 = std::get<2>(edges[0]);
    int key1 = std::get<2>(edges[1]);

    EXPECT_TRUE(g.has_edge(1, 2, key0));
    EXPECT_TRUE(g.has_edge(1, 2, key1));
    EXPECT_FALSE(g.has_edge(2, 1, key0));  // directed
}

TEST(MultiDiGraphTest, EdgeAttributes) {
    MultiDiGraph g;
    g.add_edge(1, 2, {{"label", "x"}});
    g.add_edge(1, 2, {{"label", "y"}});

    std::set<std::string> labels;
    for (const auto& [u, v, k] : g.edges()) {
        labels.insert(g._multi_adj[u][v][k].at("label"));
    }

    EXPECT_EQ(labels.size(), 2);
    EXPECT_TRUE(labels.count("x"));
    EXPECT_TRUE(labels.count("y"));
}

TEST(MultiDiGraphTest, DegreeCountsAllEdges) {
    MultiDiGraph g;
    g.add_edge(1, 2);
    g.add_edge(1, 2);
    g.add_edge(2, 3);

    auto deg = g.degree();
    EXPECT_EQ(deg[1], 2);
    EXPECT_EQ(deg[2], 1);  // only out-edges counted
}

TEST(MultiDiGraphTest, NeighborsCorrect) {
    MultiDiGraph g;
    g.add_edge(1, 2);
    g.add_edge(1, 3);
    g.add_edge(1, 2);

    auto nbrs = g.neighbors(1);
    std::set<int> nbr_set(nbrs.begin(), nbrs.end());

    EXPECT_EQ(nbr_set.size(), 2);
    EXPECT_TRUE(nbr_set.count(2));
    EXPECT_TRUE(nbr_set.count(3));
}

TEST(MultiDiGraphTest, CopyPreservesGraph) {
    MultiDiGraph g;
    g.add_edge(1, 2);
    g.add_edge(1, 2);
    g.add_edge(2, 3);

    MultiDiGraph g2 = g.copy();
    EXPECT_EQ(static_cast<int>(g2.size()), 3);
    EXPECT_TRUE(g2.has_edge(1, 2));
    EXPECT_TRUE(g2.has_edge(2, 3));
}

TEST(MultiDiGraphTest, ClearEdgesPreservesNodes) {
    MultiDiGraph g;
    g.add_node(1, {{"color", "red"}});
    g.add_node(2);
    g.add_edge(1, 2);
    g.add_edge(1, 2);

    g.clear_edges();

    EXPECT_EQ(static_cast<int>(g.size()), 0);
    EXPECT_TRUE(g.has_node(1));
    EXPECT_TRUE(g.has_node(2));
    EXPECT_EQ(g._node.at(1).at("color"), "red");
}

TEST(MultiDiGraphTest, IsMultigraphAndDirected) {
    MultiDiGraph g;
    EXPECT_TRUE(g.is_multigraph());
    EXPECT_TRUE(g.is_directed());
}

TEST(MultiDiGraphTest, SizeWithWeights) {
    MultiDiGraph g;
    g.add_edge(1, 2, {{"w", "1.5"}});
    g.add_edge(1, 2, {{"w", "2.5"}});
    g.add_edge(2, 3, {{"w", "3.0"}});

    EXPECT_DOUBLE_EQ(g.size("w"), 7.0);
}

TEST(MultiDiGraphTest, ToUndirectedCreatesMultiGraph) {
    MultiDiGraph g;
    g.add_edge(1, 2, {{"x", "a"}});
    g.add_edge(1, 2, {{"x", "b"}});

    MultiGraph undirected = g.to_undirected();
    EXPECT_TRUE(undirected.is_multigraph());
    EXPECT_FALSE(undirected.is_directed());

    std::map<std::string, int> label_count;
    for (const auto& [u, v, k] : undirected.edges()) {
        label_count[undirected._multi_adj[u][v][k]["x"]]++;
        label_count[undirected._multi_adj[v][u][k]["x"]]++;
    }

    EXPECT_EQ(label_count["a"], 2); // both directions
    EXPECT_EQ(label_count["b"], 2);
}
