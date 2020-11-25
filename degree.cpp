#include "degree.h"

#include <sstream>
#include <fstream>
#include <vector>

degree::degree(): _g(false, true)
{
    
}

void degree::readFromData()
{  
    std::ifstream file("routedata");
    if(!file.is_open()) return;
    string line, word;
    std::vector<string> routes;
    while(file >> line)
    {
        routes.clear();
        std::stringstream ss(line);
        while(getline(ss, word))
        {
            routes.push_back(word);
        }
        std::string source = routes[3];
        std::string destination = routes[5];

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
            _g.setEdgeWeight(source, destination, getEdgeWeight(source, destination) + 1);
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