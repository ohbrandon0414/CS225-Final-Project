#include "degree.h"

#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>
#include <string>

#include "line.h"
#include "color.h"
#include "circle.h"
#include "vector2.h"
#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"

using namespace cs225;
using cs225::HSLAPixel;

degree::degree(std::string routefile, std::string airportfile)
    : _g(true, true), r_file(routefile), a_file(airportfile) {}

void degree::readFromData()
{  
    std::ifstream file(r_file);
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
    PNG map;
    map.readFromFile("map.png");

    std::vector<std::pair<Vertex, int>> weights(node_weight.begin(), node_weight.end());
    std::sort(weights.begin(), weights.end(), [](std::pair<Vertex, int>a, std::pair<Vertex, int>b){return a.second > b.second;});
    int max = weights[0].second;
    int twothird = (max / 3) * 2;
    int onethird = max / 3;
    
    const HSLAPixel high = color::RED;
    const HSLAPixel medium = color::GREEN;
    const HSLAPixel low = color::BLUE;

    int minimum_radius = 3;
    
    std::vector<Edge> edges = _g.getEdges();
    for(auto& i : edges)
    {
        HSLAPixel used;
        std::string source = i.source;
        std::string dest = i.dest;
        double s_lat = locations[source].first;
        double s_long = locations[source].second;
        double d_lat = locations[dest].first;
        double d_long = locations[dest].second;
        s_lat = (989 - (s_lat * 10.993)) < 5 ? 5 : 989 - (s_lat * 10.993);
        s_long = (1908.5 + (s_long * 10.603)) < 5 ? 5 : 1908.5 + (s_long * 10.603);
        d_lat = (989 - (d_lat * 10.993)) < 5 ? 5 : 989 - (d_lat * 10.993);
        d_long = (1908.5 + (d_long * 10.603)) < 5 ? 5 : 1908.5 + (d_long * 10.603);
        if(node_weight[source] > onethird && node_weight[dest] > onethird)
        {
            used = color::YELLOW;
        }
        else{
            used = color::GRAY;
        }
        Line line(Vector2(s_long, s_lat), Vector2(d_long, d_lat), used);
        line.draw(&map);
    }
    for(auto & i : weights)
    {
        std::string airport_name = i.first;
        int weight = i.second;
        double latitude = locations[airport_name].first;
        double longitude = locations[airport_name].second;
        HSLAPixel used;
        int radius = minimum_radius;
        if(weight <= onethird)
        {
            used = low;
        } else if(weight > onethird && weight <= twothird)
        {
            used = medium;
            radius +=5;
        }
        else{
            used = high;
            radius += 10;
        }
        latitude = (989 - (latitude * 10.993)) < 5 ? 5 : 989 - (latitude * 10.993);
        longitude = (1908.5 + (longitude * 10.603)) < 5 ? 5 : 1908.5 + (longitude * 10.603);
        Circle c(Vector2( longitude, latitude), used, radius);
        c.draw(&map);
    }
    map.writeToFile("out.png");
}

void degree::readFromAirport()
{
    std::vector<std::string> data;
    std::ifstream file(a_file);
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

std::unordered_map<std::string, std::pair<double, double>> degree::getLocations(){
    return locations;
}