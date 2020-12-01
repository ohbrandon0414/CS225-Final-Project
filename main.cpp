#include "degree.h"
#include "bfs.h"

#include <iostream>

int main()
{
    degree d;
    d.readFromData();
    d.drawOnMap();

    std::cout << std::endl;

    BFS bfs("test.txt");
    bfs.printResult();
}