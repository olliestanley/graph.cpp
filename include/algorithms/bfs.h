#ifndef BFS_H
#define BFS_H

#include <vector>
#include "graph.h"
#include "utils/generator.h"

std::vector<Graph::Node> bfs(const Graph &G, const Graph::Node &start);

Generator<Graph::Node> bfs_generator(const Graph &G, const Graph::Node &start);

#endif
