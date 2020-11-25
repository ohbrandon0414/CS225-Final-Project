#include "degree.h"

#include <sstream>
#include <fstream>
#include <vector>

degree::degree(): _g(false, true)
{
    
}

void degree::readFromData()
{  
    std::ifstream file("routedata");
    if(!file.is_open()) return;
    string line, word;
    std::vector<string> routes;
    while(file >> line)
    {
        routes.clear();
        std::stringstream ss(line);
        while(getline(ss, word))
        {
            routes.push_back(word);
        }
        std::string source = routes[3];
        std::string destination = routes[5];
        _g.insertVertex(source)


    }    
     
}