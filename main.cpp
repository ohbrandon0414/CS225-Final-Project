#include "degree.h"
#include "landmarkpath.h"

int main()
{
    degree d("routedata.txt", "airports_full.txt");
    // d.readFromData();
    // d.drawOnMap();
    d.readFromAirport();
    
    std::unordered_map<std::string, std::pair<double, double>> locations = d.getLocations();
    LandmarkPath lp("routedata.txt", locations);
    lp.printPath(lp.getResult("BOS", "YRI", "PVG"));
}