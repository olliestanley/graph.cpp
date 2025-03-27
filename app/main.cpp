#include <iostream>
#include "graph.h"
#include "digraph.h"
#include "algorithms/bfs.h"

void run_bfs() {
    Graph G;
    for (int i = 0; i < 6; i++)
        G.add_node(i);

    G.add_edge(0, 1, {});
    G.add_edge(0, 2, {});
    G.add_edge(1, 3, {});
    G.add_edge(1, 4, {});
    G.add_edge(2, 5, {});

    try {
        std::vector<Graph::Node> order = bfs(G, 0);
        std::cout << "BFS order starting from node 0: ";
        for (auto node : order)
            std::cout << node << " ";
        std::cout << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << "BFS order starting from node 1: ";
    for (auto node : bfs_generator(G, 1)) {
        std::cout << node << " ";
    }
}

int main() {
    Graph G;
    G.setName("MyGraph");
    G.add_node(1, {{"color", "red"}});
    G.add_node(2);
    G.add_edge(1, 2, {{"weight", "3.14"}});
    std::cout << G << std::endl;
    Graph G_DG = G.to_directed();
    std::cout << G_DG << std::endl;

    DiGraph DG;
    DG.add_node(1, {{"color", "red"}});
    DG.add_node(2);
    DG.add_edge(1, 2, {{"weight", "3.14"}});
    std::cout << DG << std::endl;
    Graph DG_G = DG.to_undirected();
    std::cout << DG_G << std::endl;

    run_bfs();
    return 0;
}
