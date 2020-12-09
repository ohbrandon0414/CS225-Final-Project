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
        /**
         * Landmark Path constructor
         * @param routefile name of the file with route data
         * @param airports map containing all the IATA names of the airports, corresponding to its location
         */
        LandmarkPath(const string  & routefile, unordered_map<string, pair<double, double>> airports);

        /**
         * Finds the landmark path through the 3 given vertices
         * @param source the starting point of the path to find
         * @param landmark the midpoint that the path must go through
         * @param destination the end point that the path must get to
         */
        vector<Vertex> getResult(Vertex source, Vertex landmark, Vertex destination);

        /**
         * Helper method that finds the shortest path given 2 vertices
         * @param start the starting point of the path
         * @param target the end point the path must get to using the shortest path
         * @return vector containing the in order path from start to target
         */
        vector<Vertex> getShortestPath(Vertex start, Vertex target);

        /**
         * Prints the path of the landmark path
         */
        void printPath(vector<Vertex> path);

        /**
         * Getter for the graph created for landmark path
         * @return initialized graph
         */
        Graph getGraph();

        // Used for defining how the priority queue sorts itself
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