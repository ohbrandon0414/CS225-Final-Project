#pragma once

#include "graph.h"
#include <queue>
#include <vector>
#include <iostream>

class LandmarkPath {
    public:
    LandmarkPath(const std::string  & routefile, std::unordered_map<std::string, std::pair<double, double>> airports);
    void getResult(std::string source, std::string landmark, std::string destination);
    

    private:
    long double toRadians(const long double degree);
    long double distance(long double lat1, long double long1, 
					long double lat2, long double long2);

};