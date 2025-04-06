#include "multigraph.h"
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
