#ifndef DFS_H
#define DFS_H

#include <vector>
#include "graph.h"
#include "utils/generator.h"

std::vector<Graph::Node> dfs(const Graph &G, const Graph::Node &start);

Generator<Graph::Node> dfs_generator(const Graph &G, const Graph::Node &start);

#endif
