#pragma once

#include "edge.h"
#include "graph.h"

#include <unordered_map>

class degree
{
    private:
        Graph _g;
        std::unordered_map<Vertex, int> node_weight;
    public:
        degree();
        void readFromData();
        void drawOnMap();
};