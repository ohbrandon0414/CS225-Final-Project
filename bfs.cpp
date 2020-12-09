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
    // Take file with routes for reading
    std::ifstream file(filename);
    if(!file.is_open()) return;
    string line, word;
    vector<string> routes;
    Vertex start = "";

    // Take each line in the file to get the route
    while(file >> line) {
        routes.clear();
        std::stringstream ss(line);
        while(getline(ss, word, ',')) {
            routes.push_back(word);
        }

        // The 2nd and 4th attribute correspond to the source airport and the destination airport respectively
        std::string source = routes[2];
        if (start == "") start = source;
        std::string destination = routes[4];

        // If either airport is not already in graph, add it
        if(!(graph_.vertexExists(source))) {   
            graph_.insertVertex(source);
        }
        if(!(graph_.vertexExists(destination))) {   
            graph_.insertVertex(destination);
        }

        // If the edge is not in the graph, add it and set the state to unexplored
        if(!(graph_.edgeExists(source, destination))) {   
            graph_.insertEdge(source, destination);
            graph_.setEdgeLabel(source, destination, UNEXPLORED);
        }
    }

    // Graph is completely initialized, so start running the traversal
    runBFS(start);
}

void BFS::runBFS(Vertex start) {
    // First go through graph and set every vertex to the unexplored state
    for (Vertex v : graph_.getVertices()) {
        vertex_labels.insert({v, UNEXPLORED});
    }

    // Start traversal on the start vertex
    bfsHelper(start);

    // Continue looping through all the vertices, checking for separate cycles in the graph that still need to be traversed
    for (Vertex v : graph_.getVertices()) {
        if (vertex_labels[v] == UNEXPLORED) {
            bfsHelper(v);
        }
    }
}

void BFS::bfsHelper(Vertex v) {
    // The breadth first search algorithm
    // Create a queue and add the starting vertex, labeling it as visited
    queue<Vertex> q;
    vertex_labels[v] = VISITED;
    q.push(v);

    while (!q.empty()) {
        // Vertex of interest is the first vertex in the queue, and push into the results vector as you visit it
        v = q.front();
        bfs_result.push_back(v);
        q.pop();

        // Check all adjacent vertices of current vertex, if not visited before, then add to queue
        // Also check if edge is a discovery or cross edge and set the edge label to the corresponding state
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
    // Open to file streams and save the path and edge results to 2 separate files
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
    edges_file.close();
}