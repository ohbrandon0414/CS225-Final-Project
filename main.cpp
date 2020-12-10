#include "degree.h"
#include "bfs.h"
#include "landmarkpath.h"

int main()
{
    degree d("routedata.txt", "airports_full.txt");
    BFS bfs("routedata.txt");
    std::unordered_map<std::string, std::pair<double, double>> locations = d.getLocations();
    LandmarkPath lp("routedata.txt", locations);

    while(1)
    {  
        std::cout<<"Type degree, bfs or landmark"<<'\n';
        std::string input;
        std::cin>>input;
        if(input == "degree")
        {
            d.readFromData();
            d.drawOnMap();
            d.readFromAirport();
            std::cout<<"Out.png created"<<'\n';
        }
        if(input == "bfs")
        {
            bfs.saveResult("path.txt", "edges.txt");
            std::cout<<'\n';
        }
        if(input == "landmark")
        {
            lp.printPath(lp.getResult("BOS", "YRI", "PVG"));
            std::cout<<'\n';
        }
    }
}