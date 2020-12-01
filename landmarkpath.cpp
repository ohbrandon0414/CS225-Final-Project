#include "landmarkpath.h"

LandmarkPath::LandmarkPath(const std::string  & routefile, std::unordered_map<std::string, std::pair<double, double>> airports){
    Graph g(true);
    std::ifstream file(routefile);
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
        int weight = LandmarkPath::distance(airports.at(source).first, airports.at(source).second,
                    airports.at(destination).first,airports.at(destination).second);
        if(!(g.edgeExists(source, destination))) {   
            g.insertEdge(source, destination);
            g.setEdgeWeight(source, destination, weight);
        }
    }
}

void LandmarkPath::getResult(Graph g, std::string source, std::string landmark, std::string destination) {
    
}

void LandmarkPath::getShortestPath(Graph g, Vertex start){
	unordered_map<Vertex, int> dis; //initialize tentative distance value
	unordered_map<Vertex, Vertex> prev; // initialize a map that maps current node -> its previous node
	unordered_map<Vertex, bool> visted; 
	std::queue<std::pair<Vertex, int>> p_q; // initialize the priority queue
	for (Vertex v: g.getVertices()){
		dis[v] = INT_MAX;
		prev[v] = nullptr;
	}
	dis[start] = 0;
	p_q.push(std::pair<Vertex, int>(start, 0));
	while(!p_q.empty()){

	}
}



Vertex getMin(unordered_map<Vertex, int> dis, unordered_map<Vertex, bool> visited){
	int min_d = INT_MAX;
	Vertex min_v;
	for (auto i: dis) {
		if(!visited.at(i.first) && i.second <= min_d){
			min_d = i.second;
			min_v = i.first;
		}
	}
	return min_v;
}




// C++ program to calculate Distance 
// Between Two Points on Earth 
// #include <bits/stdc++.h> 
using namespace std; 

// Utility function for 
// converting degrees to radians 
long double LandmarkPath::toRadians(const long double degree) 
{ 
	// cmath library in C++ 
	// defines the constant 
	// M_PI as the value of 
	// pi accurate to 1e-30 
	long double one_deg = (M_PI) / 180; 
	return (one_deg * degree); 
} 

long double LandmarkPath::distance(long double lat1, long double long1, long double lat2, long double long2) 
{ 
	// Convert the latitudes 
	// and longitudes 
	// from degree to radians. 
	lat1 = toRadians(lat1); 
	long1 = toRadians(long1); 
	lat2 = toRadians(lat2); 
	long2 = toRadians(long2); 
	
	// Haversine Formula 
	long double dlong = long2 - long1; 
	long double dlat = lat2 - lat1; 

	long double ans = pow(sin(dlat / 2), 2) + 
						cos(lat1) * cos(lat2) * 
						pow(sin(dlong / 2), 2); 

	ans = 2 * asin(sqrt(ans)); 

	// Radius of Earth in 
	// Kilometers, R = 6371 
	// Use R = 3956 for miles 
	long double R = 6371; 
	
	// Calculate the result 
	ans = ans * R; 

	return ans; 
} 

// This code is contributed 
// by Aayush Chaturvedi 

