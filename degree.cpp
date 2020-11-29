#include "degree.h"

#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>
#include <string>

degree::degree(): _g(true, true)
{
    
}

void degree::readFromData()
{  
    std::ifstream file("routedata.txt");
    if(!file.is_open()) return;
    std::string line, word;
    std::vector<std::string> routes;
    while(file >> line)
    {
        routes.clear();
        std::stringstream ss(line);
        while(getline(ss, word, ','))
        {
            routes.push_back(word);
        }
        std::string source = routes[2];
        std::string destination = routes[4];

        if(!(_g.vertexExists(source)))
        {   
            _g.insertVertex(source);
        }
        if(!(_g.vertexExists(destination)))
        {   
            _g.insertVertex(destination);
        }
        if(!(_g.edgeExists(source, destination)))
        {   
            _g.insertEdge(source, destination);
            _g.setEdgeWeight(source, destination, 0);
        }
        else{
            _g.setEdgeWeight(source, destination, _g.getEdgeWeight(source, destination) + 1);
        }

        if(node_weight.find(source) != node_weight.end())
        {
            node_weight[source]++;
        }
        else{
            node_weight[source] = 0;
        }
        if(node_weight.find(destination) != node_weight.end())
        {
            node_weight[destination]++;
        }
        else{
            node_weight[destination] = 0;
        }

    }    
}

     

    void degree::drawOnMap()
    {
        std::vector<std::pair<Vertex, int>> weights(node_weight.begin(), node_weight.end());
        std::sort(weights.begin(), weights.end(), [](std::pair<Vertex, int>a, std::pair<Vertex, int>b){return a.second > b.second;});
        int max = weights[0].second;
    }