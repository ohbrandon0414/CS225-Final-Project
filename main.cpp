#include "degree.h"
#include "bfs.h"
#include "landmarkpath.h"
#include "graph.h"
#include "util.hpp"

#include <map>
#include <vector>

using std::map;
using std::vector;

namespace opts
{
    bool help = false;
    bool map = false;
    bool bfs = false;
    bool lmp = false;
}

int main(int argc, const char** argv) {
    string source = "BOS";
    string landmark = "CMI";
    string dest = "PVG";

    OptionsParser optsparse;
    optsparse.addArg(source);
    optsparse.addArg(landmark);
    optsparse.addArg(dest);
    optsparse.addOption("help", opts::help);
    optsparse.addOption("h", opts::help);
    optsparse.addOption("map", opts::map);
    optsparse.addOption("m", opts::map);
    optsparse.addOption("bfs", opts::bfs);
    optsparse.addOption("b", opts::bfs);
    optsparse.addOption("landmarkpath", opts::lmp);
    optsparse.addOption("l", opts::lmp);
    optsparse.parse(argc, argv);

    if (opts::help) {
        cout << "Usage: " << argv[0] << endl;
        cout << "-m/--map: map functionality" << endl;
        cout << "-b/--bfs: bfs traversal" << endl;
        cout << "-l/--landmarkpath [source] [landmark] [destination]: landmark path between 3 airports" << endl;
    }

    if (opts::map) {
        degree d("routedata.txt", "airports_full.txt");
        d.readFromData();
        d.readFromAirport();
        d.drawOnMap();
    }

    if (opts::bfs) {
        BFS bfs("routedata.txt");
        bfs.saveResult("path.txt", "edges.txt");
    }

    if (opts::lmp) {
        degree d("routedata.txt", "airports_full.txt");
        d.readFromAirport();
        std::unordered_map<std::string, std::pair<double, double>> locations = d.getLocations();
        LandmarkPath lp("tests/small_routedata.txt", locations);
        lp.getResult(source, landmark, dest);
    }
    
    return 0;
}