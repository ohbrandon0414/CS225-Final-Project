#pragma once

#include "graph.h"
#include <queue>
#include <vector>
#include <iostream>
#include <math.h> 

using std::string;
using std::unordered_map;
using std::pair;
using std::priority_queue;

class LandmarkPath {
    public:
    LandmarkPath(const string  & routefile, unordered_map<string, pair<double, double>> airports);
    void getResult(Graph g, Vertex, Vertex landmark, Vertex destination);
    void getShortestPath(Graph g, Vertex start);

    struct compare {
        bool operator() (const pair<Vertex, int> & a, const pair<Vertex, int> & b) {
            return a.second > b.second;
        }
    };

    private:
    long double toRadians(const long double degree);
    long double distance(long double lat1, long double long1, 
					long double lat2, long double long2);
    Vertex getMin(unordered_map<Vertex, int> dis, unordered_map<Vertex, bool> visited); 
};