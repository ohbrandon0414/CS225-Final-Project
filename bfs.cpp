#include "bfs.h"

const string BFS::UNEXPLORED = "UNEXPLORED";
const string BFS::VISITED = "VISITED";
const string BFS::DISCOVERY = "DISCOVERY";
const string BFS::CROSS = "CROSS";

BFS::BFS(string filename) {
    Graph g(false);
    std::ifstream file(filename);
    if(!file.is_open()) return;
    string line, word;
    vector<string> routes;
    while(file >> line) {
        routes.clear();
        std::stringstream ss(line);
        while(getline(ss, word, ',')) {
            routes.push_back(word);
        }
        std::string source = routes[2];
        std::string destination = routes[4];

        if(!(g.vertexExists(source))) {   
            g.insertVertex(source);
        }
        if(!(g.vertexExists(destination))) {   
            g.insertVertex(destination);
        }
        if(!(g.edgeExists(source, destination))) {   
            g.insertEdge(source, destination);
        }
    }
    runBFS(g);
}

void BFS::runBFS(Graph g) {
    for (Vertex v : g.getVertices()) {
        vertex_labels.insert({v, UNEXPLORED});
    }
    for (Edge e : g.getEdges()) {
        e.setLabel(UNEXPLORED);
    }
    for (Vertex v : g.getVertices()) {
        if (vertex_labels[v] == UNEXPLORED) {
            runBFS(g, v);
        }
    }
}

void BFS::runBFS(Graph g, Vertex v) {
    queue<Vertex> q;
    vertex_labels[v] = VISITED;
    q.push(v);

    while (!q.empty()) {
        v = q.front();
        bfs_result.push_back(v);
        q.pop();
        for (Vertex w : g.getAdjacent(v)) {
            if (vertex_labels[w] == UNEXPLORED) {
                g.getEdge(v, w).setLabel(DISCOVERY);
                vertex_labels[w] = VISITED;
                q.push(w);
            } else if (g.getEdge(v, w).getLabel() == UNEXPLORED) {
                g.getEdge(v, w).setLabel(CROSS);
            }
        }
    }
}

void BFS::printResult() {
    
    for (Vertex v : bfs_result) {
        std::cout << v << std::endl;
    }
}