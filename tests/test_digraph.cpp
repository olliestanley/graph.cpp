#include "digraph.h"
#include <gtest/gtest.h>

TEST(DiGraphTest, AddDirectedEdge) {
    DiGraph g;
    g.add_edge(1, 2);
    EXPECT_TRUE(g.has_edge(1, 2));
    EXPECT_FALSE(g.has_edge(2, 1));
    EXPECT_EQ(g.number_of_edges(), 1);
}

TEST(DiGraphTest, DirectedRemoveEdge) {
    DiGraph g;
    g.add_edge(1, 2);
    EXPECT_TRUE(g.has_edge(1, 2));
    g.remove_edge(1, 2);
    EXPECT_FALSE(g.has_edge(1, 2));
}

TEST(DiGraphTest, DirectedEdgeCountWeighted) {
    DiGraph g;
    g.add_edge(1, 2, {{"weight", "1.5"}});
    g.add_edge(2, 3, {{"weight", "2.5"}});
    EXPECT_DOUBLE_EQ(g.size("weight"), 4.0);
}

TEST(DiGraphTest, DirectedToUndirected) {
    DiGraph g;
    g.add_edge(1, 2, {{"label", "a"}});
    g.add_edge(2, 3, {{"label", "b"}});

    Graph ug = g.to_undirected();
    EXPECT_TRUE(ug.has_edge(1, 2));
    EXPECT_TRUE(ug.has_edge(2, 1));
    EXPECT_TRUE(ug.has_edge(3, 2));
    EXPECT_TRUE(ug.has_edge(2, 3));
    EXPECT_EQ(ug.number_of_edges(), 2); // undirected = symmetric, but still 2 edges
}

TEST(DiGraphTest, DirectedCopy) {
    DiGraph g;
    g.setName("Original");
    g.add_edge(1, 2);
    g.add_edge(3, 4);

    DiGraph g2 = g.copy();
    EXPECT_TRUE(g2.has_edge(1, 2));
    EXPECT_TRUE(g2.has_edge(3, 4));
    EXPECT_EQ(g2.getName(), "Original");
    EXPECT_EQ(g2.number_of_edges(), 2);
}

TEST(DiGraphTest, IsDirected) {
    DiGraph g;
    EXPECT_TRUE(g.is_directed());
    EXPECT_FALSE(g.is_multigraph());
}
