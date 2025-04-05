#include "graph.h"
#include "algorithms/bfs.h"
#include "algorithms/dfs.h"
#include "utils/generator.h"
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

TEST(GraphTest, BFSOrder) {
    Graph g;
    g.add_edge(1, 2);
    g.add_edge(1, 3);
    g.add_edge(2, 4);
    g.add_edge(2, 5);
    g.add_edge(3, 6);
    g.add_edge(3, 7);
    Graph::Node start = 1;
    std::vector<Graph::Node> order = bfs(g, start);
    std::vector<Graph::Node> expectedOrder = {1, 2, 3, 4, 5, 6, 7};
    EXPECT_EQ(order, expectedOrder);
}

TEST(GraphTest, BFSGenerator) {
    Graph g;
    g.add_edge(1, 2);
    g.add_edge(1, 3);
    g.add_edge(2, 4);
    g.add_edge(2, 5);
    g.add_edge(3, 6);
    g.add_edge(3, 7);
    Graph::Node start = 1;
    Generator<Graph::Node> order = bfs_generator(g, start);
    std::vector<Graph::Node> expectedOrder = {1, 2, 3, 4, 5, 6, 7};
    for (Graph::Node node : order) {
        EXPECT_EQ(node, expectedOrder.front());
        expectedOrder.erase(expectedOrder.begin());
    }
    EXPECT_TRUE(expectedOrder.empty());
}

TEST(GraphTest, DFSOrder) {
    Graph g;
    g.add_edge(1, 2);
    g.add_edge(1, 3);
    g.add_edge(2, 4);
    g.add_edge(2, 5);
    g.add_edge(3, 6);
    g.add_edge(3, 7);
    Graph::Node start = 1;
    std::vector<Graph::Node> order = dfs(g, start);
    std::vector<Graph::Node> expectedOrder = {1, 2, 4, 5, 3, 6, 7};
    EXPECT_EQ(order, expectedOrder);
}

TEST(GraphTest, DFSGenerator) {
    Graph g;
    g.add_edge(1, 2);
    g.add_edge(1, 3);
    g.add_edge(2, 4);
    g.add_edge(2, 5);
    g.add_edge(3, 6);
    g.add_edge(3, 7);
    Graph::Node start = 1;
    Generator<Graph::Node> order = dfs_generator(g, start);
    std::vector<Graph::Node> expectedOrder = {1, 2, 4, 5, 3, 6, 7};
    for (Graph::Node node : order) {
        EXPECT_EQ(node, expectedOrder.front());
        expectedOrder.erase(expectedOrder.begin());
    }
    EXPECT_TRUE(expectedOrder.empty());
}
