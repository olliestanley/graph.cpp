#include "graph.h"
#include "algorithms/dfs.h"
#include "utils/generator.h"
#include <gtest/gtest.h>

TEST(DFSTest, DFSOrder) {
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

TEST(DFSTest, DFSGenerator) {
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