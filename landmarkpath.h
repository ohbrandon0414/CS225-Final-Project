#pragma once

#include "graph.h"
#include <queue>
#include <stack>
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
    void getResult(Vertex, Vertex landmark, Vertex destination);
    vector<Vertex> getShortestPath(Vertex start, Vertex target);
    void printPath(vector<Vertex> path);

    struct compare {
        bool operator() (const pair<Vertex, int> & a, const pair<Vertex, int> & b) {
            return a.second > b.second;
        }
    };

    private:
    long double toRadians(const long double degree);
    long double distance(long double lat1, long double long1, 
					long double lat2, long double long2);

    Graph g_;
};