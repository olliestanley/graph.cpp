#include <iostream>
#include "graph.h"

int main() {
    Graph G;
    G.setName("MyGraph");
    G.add_node(1, {{"color", "red"}});
    G.add_node(2);
    G.add_edge(1, 2, {{"weight", "3.14"}});
    std::cout << G << std::endl;
    return 0;
}
