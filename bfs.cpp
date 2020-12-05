/**
 * @file bfs.cpp
 * Implementation of the BFS class.
 */

#include "bfs.h"

const string BFS::UNEXPLORED = "UNEXPLORED";
const string BFS::VISITED = "VISITED";
const string BFS::DISCOVERY = "DISCOVERY";
const string BFS::CROSS = "CROSS";

BFS::BFS(string filename) : graph_(false) {
    std::ifstream file(filename);
    if(!file.is_open()) return;
    string line, word;
    vector<string> routes;
    Vertex start = "";
    while(file >> line) {
        routes.clear();
        std::stringstream ss(line);
        while(getline(ss, word, ',')) {
            routes.push_back(word);
        }
        std::string source = routes[2];
        if (start == "") start = source;
        std::string destination = routes[4];

        if(!(graph_.vertexExists(source))) {   
            graph_.insertVertex(source);
        }
        if(!(graph_.vertexExists(destination))) {   
            graph_.insertVertex(destination);
        }
        if(!(graph_.edgeExists(source, destination))) {   
            graph_.insertEdge(source, destination);
            graph_.setEdgeLabel(source, destination, UNEXPLORED);
        }
    }
    runBFS(start);
}

void BFS::runBFS(Vertex start) {
    for (Vertex v : graph_.getVertices()) {
        vertex_labels.insert({v, UNEXPLORED});
    }
    bfsHelper(start);
    for (Vertex v : graph_.getVertices()) {
        if (vertex_labels[v] == UNEXPLORED) {
            bfsHelper(v);
        }
    }
}

void BFS::bfsHelper(Vertex v) {
    queue<Vertex> q;
    vertex_labels[v] = VISITED;
    q.push(v);

    while (!q.empty()) {
        v = q.front();
        bfs_result.push_back(v);
        q.pop();
        for (Vertex w : graph_.getAdjacent(v)) {
            if (vertex_labels[w] == UNEXPLORED) {
                graph_.setEdgeLabel(v, w, DISCOVERY);
                edge_result.push_back(graph_.getEdge(v, w));
                vertex_labels[w] = VISITED;
                q.push(w);
            } else if (graph_.getEdge(v, w).getLabel() == UNEXPLORED) {
                graph_.setEdgeLabel(v, w, CROSS);
                edge_result.push_back(graph_.getEdge(v, w));
            }
        }
    }
}

void BFS::printResult() { 
    for (Vertex v : bfs_result) {
        std::cout << v << std::endl;
    }
}

void BFS::saveResult(string pathfile, string edgefile) {
    std::ofstream path_file;
    path_file.open(pathfile);
    for (Vertex v : bfs_result) {
        path_file << v << "\n";
    }
    path_file.close();
    std::ofstream edges_file;
    edges_file.open(edgefile);
    for (Edge e : edge_result) {
        edges_file << e.source + "<-->" + e.dest + " " + e.getLabel() + "\n";
    }
    // for (Edge e : graph_.getEdges()) {
    //     edges_file << e.source + "<-->" + e.dest + " " + e.getLabel() + "\n";
    // }
    edges_file.close();
}