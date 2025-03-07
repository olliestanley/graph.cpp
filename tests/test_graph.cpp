#include "graph.h"
#include <gtest/gtest.h>

TEST(GraphTest, AddNode) {
    Graph g;
    g.add_node(1);
    EXPECT_TRUE(g.has_node(1));
    EXPECT_EQ(g.number_of_nodes(), 1);
}

TEST(GraphTest, AddEdge) {
    Graph g;
    g.add_edge(1, 2);
    EXPECT_TRUE(g.has_edge(1, 2));
    EXPECT_TRUE(g.has_edge(2, 1));
    EXPECT_EQ(g.number_of_edges(), 1);
}

TEST(GraphTest, RemoveNode) {
    Graph g;
    g.add_node(1);
    g.add_node(2);
    g.add_edge(1, 2);
    g.remove_node(1);
    EXPECT_FALSE(g.has_node(1));
    EXPECT_EQ(g.number_of_nodes(), 1);
    EXPECT_FALSE(g.has_edge(1, 2));
}

TEST(GraphTest, GraphName) {
    Graph g;
    g.setName("MyGraph");
    EXPECT_EQ(g.getName(), "MyGraph");
    std::string expectedStr = "Graph named 'MyGraph' with 0 nodes and 0 edges";
    EXPECT_EQ(g.str(), expectedStr);
}
