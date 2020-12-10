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

   /* 
 *   readFromData
 *   DESCRIPTION: Reads in the routes data
 *   INPUTS: None
 *   OUTPUTS: None
 *   RETURN VALUE: None
 *   SIDE EFFECTS: sets up the vertex and edges for the airport route
 */
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

    /* 
 *   readFromAirport
 *   DESCRIPTION: Reads in airport data
 *   INPUTS: None
 *   OUTPUTS: None
 *   RETURN VALUE: None
 *   SIDE EFFECTS: Sets up the unordered map to be plotted onto the world map
 */
    void degree::readFromAirport()
    {
        std::vector<std::string> data;
        std::ifstream file("airports.txt");
        std::string line, word;

        //go through the file and check word by word
        if(file.is_open())
        {
            while(file >> line)
            {
                data.clear();
                std::stringstream ss(line);

                while(getline(ss, word ,','))
                {
                    data.push_back(word);
                }

                // get the 3 letter keyword for airport
                std::string name = data[4];

                //save lat and long data
                double latitutde = std::stod(data[6]);
                double longitude = std::stod(data[7]);


                //insert into the unordered map
                locations[name] = make_pair(latitutde, longitude);
            }
        }
    }

