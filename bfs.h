/**
 * @file bfs.h
 * Declaration of the BFS class.
 */

#pragma once

#include "graph.h"
#include <queue>
#include <vector>
#include <iostream>
#include <fstream>

using std::queue;
using std::vector;
using std::string;
using std::unordered_map;

class BFS {
    public:
        /**
         * BFS constructor that takes in a data file name, creates the graph for the data and runs a BFS traversal on it
         * @param filename name of data file
         */
        BFS(string filename);

        /**
         * Runs a BFS traveral on the graph
         */
        void runBFS();

        /**
         * Prints list of discovery/cross edges and the ordered list of nodes visited in order
         */
        void printResult();

        /**
         * Save traversal path and edges to txt files
         */
        void saveResult(string pathfile, string edgefile);


        const static string UNEXPLORED;
        const static string VISITED;
        const static string DISCOVERY;
        const static string CROSS;

    private:
        void runBFS(Vertex v);
        Vertex start_;
        Graph graph_;
        unordered_map<Vertex, string> vertex_labels;
        vector<Vertex> bfs_result;
};