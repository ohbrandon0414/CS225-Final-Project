#include "degree.h"
#include "bfs.h"
#include "landmarkpath.h"

int main()
{
    degree d("routedata.txt", "airports_full.txt");
    d.readFromData();
    d.drawOnMap();
    d.readFromAirport();

    BFS bfs("routedata.txt");
    bfs.saveResult("path.txt", "edges.txt");
    
    std::unordered_map<std::string, std::pair<double, double>> locations = d.getLocations();
    LandmarkPath lp("routedata.txt", locations);
    lp.getResult("BOS", "SMF", "PVG");
}