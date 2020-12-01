#include "degree.h"
#include "bfs.h"

#include <iostream>

int main()
{
    degree d;
    d.readFromData();
    d.drawOnMap();

    BFS bfs("routedata.txt");
    bfs.saveResult();
}