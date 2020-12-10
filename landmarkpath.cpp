#include "landmarkpath.h"
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define RESET   "\033[0m"


LandmarkPath::LandmarkPath(const std::string & routefile, std::unordered_map<std::string, std::pair<double, double>> airports) : g_(true) {
	// First opens route file and adds all routes to the graph
    std::ifstream file(routefile);
    if (!file.is_open()) return;
    string line, word;
    vector<string> routes;
    while (file >> line) {
        routes.clear();
        std::stringstream ss(line);
        while (getline(ss, word, ',')) {
            routes.push_back(word);
        }
        string source = routes[2];
        string destination = routes[4];

		// Only adds routes if the airports in the route have defined locations	
		if (airports.find(source) != airports.end() && airports.find(destination) != airports.end()) {
			if (!(g_.vertexExists(source))) {   
				g_.insertVertex(source);
			}
			if (!(g_.vertexExists(destination))) {   
				g_.insertVertex(destination);
			}

			// Set weight of the edges to be the calculated distance from source airport to destination airport
			int weight = LandmarkPath::distance(airports.at(source).first, airports.at(source).second,
						airports.at(destination).first,airports.at(destination).second) * 1000;
			if (!(g_.edgeExists(source, destination))) {   
				g_.insertEdge(source, destination);
				g_.setEdgeWeight(source, destination, weight);
			}
		}
    }
}

vector<Vertex> LandmarkPath::getResult(Vertex source, Vertex landmark, Vertex destination) {
	// Combine the shortest path from source to landmark + landmark to destination
	vector<Vertex> shortest_path1 = getShortestPath(source, landmark);
	vector<Vertex> shortest_path2 = getShortestPath(landmark, destination);
	// if there was an error when getting the shortest path then one of them would be empty
	if (shortest_path2.empty() || shortest_path1.empty()) {
		std::cout << "There is no path from "<< BOLDGREEN << source << RESET <<" through "
		<< BOLDGREEN<< landmark << RESET <<" to "<< BOLDGREEN << destination<< RESET << std::endl;
		//returns an empty vector
		return vector<Vertex>();
	}
	shortest_path2.insert(shortest_path2.end(), shortest_path1.begin() + 1, shortest_path1.end());
	// prints the airports to go through
	printPath(shortest_path2,  source,  landmark,  destination);
	return shortest_path2;
}

vector<Vertex> LandmarkPath::getShortestPath(Vertex start, Vertex target) {
	unordered_map<Vertex, int> dis; // initialize tentative distance value
	unordered_map<Vertex, Vertex> prev; // initialize a map that maps current node -> its previous node
	unordered_map<Vertex, bool> visited; 
	vector<Vertex> s_path;
	priority_queue<pair<Vertex, int>, vector<pair<Vertex, int>>, compare> p_q; // initialize the min distance priority queue

	// Set all vertice distances to essentially infinity and its previous vertex to "null"
	for (Vertex v : g_.getVertices()){
		dis[v] = INT_MAX;
		prev[v] = "";
	}

	// Set distance of starting vertex to itself to be 0
	dis[start] = 0;
	p_q.push(make_pair(start, 0));
	while(!p_q.empty()){
		Vertex u = p_q.top().first;
		p_q.pop();
		if (u == target) {
			if (prev[u] != "" || u == start) {
				while (u != "") {
					s_path.push_back(u);
					u = prev[u];
				}
			}
			break;
		}
		for (Vertex v : g_.getAdjacent(u)) {
			int alt = dis[u] + g_.getEdge(u, v).getWeight();
			if (alt < dis[v]) {
				dis[v] = alt;
				prev[v] = u;
				p_q.push(make_pair(v, alt));
			}
		}
	}
	return s_path;
}

void LandmarkPath::printPath(vector<Vertex> path, Vertex source, Vertex landmark, Vertex dest) {
	std::cout << "-----------------------------------------------------------------------------------" << std::endl;
	std::cout << "Shortest path from " << source << "-->" << landmark << "-->" << dest << std::endl;
	for (int i = path.size() - 1; i >= 0; i--) {
		if (path[i] == source || path[i] == landmark || path[i] == dest) {
			std::cout << BOLDGREEN;
		}
		std::cout << path[i] << RESET << std::endl;		
	}
	std::cout << "-----------------------------------------------------------------------------------" << std::endl;
}

Graph LandmarkPath::getGraph() {
	return g_;
}



// https://www.geeksforgeeks.org/program-distance-two-points-earth/
// C++ program to calculate Distance 
// Between Two Points on Earth 

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