#include "graph.h"
#include "algorithms/bfs.h"
#include "utils/generator.h"
#include <gtest/gtest.h>

TEST(BFSTest, BFSOrder) {
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

TEST(BFSTest, BFSGenerator) {
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
