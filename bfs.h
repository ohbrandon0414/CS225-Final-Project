/**
 * @file bfs.h
 * Declaration of the BFS class.
 */

#pragma once

#include "graph.h"
#include "edge.h"
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
         * @param start vertex to start traversal at
         */
        void runBFS(Vertex start);

        /**
         * Prints list of discovery/cross edges and the ordered list of nodes visited in order
         */
        void printResult();

        /**
         * Save traversal path and edges to txt files
         * @param pathfile name of file to save the bfs path to
         * @param edgefile name of file to save edges to
         */
        void saveResult(string pathfile, string edgefile);

        // global const variables for the different vertex/edge states
        const static string UNEXPLORED;
        const static string VISITED;
        const static string DISCOVERY;
        const static string CROSS;

    private:
        void bfsHelper(Vertex v);
        Vertex start_;
        Graph graph_;
        unordered_map<Vertex, string> vertex_labels;
        vector<Vertex> bfs_result;
        vector<Edge> edge_result;
};