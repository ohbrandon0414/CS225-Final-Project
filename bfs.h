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
        /**
         * Takes in a data file name, creates the graph for the data and runs a BFS traversal on it
         */
        BFS(string filename);

        /**
         * Given a graph, runs a BFS traveral on the graph
         */
        void runBFS(Graph g);

        /**
         * Prints list of discovery/cross edges and the ordered list of nodes visited in order
         */
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