#include <iostream>
#include "graph.h"
#include "digraph.h"

int main() {
    Graph G;
    G.setName("MyGraph");
    G.add_node(1, {{"color", "red"}});
    G.add_node(2);
    G.add_edge(1, 2, {{"weight", "3.14"}});
    std::cout << G << std::endl;

    DiGraph DG;
    DG.add_node(1, {{"color", "red"}});
    DG.add_node(2);
    DG.add_edge(1, 2, {{"weight", "3.14"}});
    std::cout << DG << std::endl;
    return 0;
}
