#pragma once

#include "graph.h"
#include <queue>
#include <vector>
#include <iostream>

using std::queue;
using std::vector;
using std::string;
using std::unordered_map;

class BFS {
public:
    BFS();
    void runBFS(Graph g);
    void printResult();

    const static string UNEXPLORED;
    const static string VISITED;
    const static string DISCOVERY;
    const static string CROSS;

private:
    void runBFS(Graph g, Vertex v);
    Vertex start_;
    unordered_map<Vertex, string> vertex_labels;
    vector<Vertex> bfs_result;
};