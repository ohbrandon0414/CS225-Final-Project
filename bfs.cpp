#include "bfs.h"

BFS::BFS() {
    Graph g(false);
    std::ifstream file("routedata.txt");
    if(!file.is_open()) return;
    std::string line, word;
    std::vector<std::string> routes;
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
    BFS(g);
}

BFS::BFS(Graph g) {
    
}