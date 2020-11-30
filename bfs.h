#pragma once

#include "graph.h"
#include <queue>

using std::queue;

class BFS {
public:
    BFS();
    BFS(Graph g);

private:
    BFS(Graph g, Vertex v);
    Vertex start_;
    queue<Vertex> traverse_;
};