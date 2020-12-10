#include "../cs225/catch/catch.hpp"
#include "../degree.h"
#include "../bfs.h"

#include <iostream>
#include <vector>
#include <cctype>
#include <locale>

#include <fstream>
#include <iterator>
#include <string>
#include <algorithm>

using std::ifstream;
using std::stringstream;
using std::istreambuf_iterator;
using std::fstream;

// Reads in 2 testing files in order to compare them
void compareFiles(string p1, string p2) {
    fstream f1, f2;
    bool flag = true;
    f1.open(p1,std::ios::in);
    if(f1.fail())
        std::cout<<"File can't be opened"<<std::endl;
    f2.open(p2,std::ios::in);
    if(f2.fail())
        std::cout<<"File can't be opened"<<std::endl;

    while(1) {
        int c1 = f1.get();
        int c2 = f2.get();
        if (c1 != c2) {
            flag=false;
            break;
        }
        if ((c1 == EOF) || (c2 == EOF))
            break;
    }
    f1.close();
    f2.close();
    if (flag == false) {
        FAIL( "Your output in \"" + p1 + "\" does not match our output in \"" + p2 + "\"");
    }
    REQUIRE(flag == true);
}

TEST_CASE("Triangle graph", "[bfs]") {
    BFS bfs("tests/triangle_test.txt");
    bfs.saveResult("test_triangle_path.txt", "test_triangle_edges.txt");
    compareFiles("tests/expected_triangle_test_path.txt", "test_triangle_path.txt");
    compareFiles("tests/expected_triangle_test_edges.txt", "test_triangle_edges.txt");
}

TEST_CASE("Small graph", "[bfs]") {
    BFS bfs("tests/small_graph_test.txt");
    bfs.saveResult("test_small_path.txt", "test_small_edges.txt");
    compareFiles("tests/expected_small_test_path.txt", "test_small_path.txt");
    compareFiles("tests/expected_small_test_edges.txt", "test_small_edges.txt");
}

TEST_CASE("Graph with 2 cycles", "[bfs]") {
    BFS bfs("tests/2cycle_test.txt");
    bfs.saveResult("test_2cycle_path.txt", "test_2cycle_edges.txt");
    string s;
    int sTotal = 0;

    ifstream in;
    in.open("test_2cycle_path.txt");

    while(!in.eof()) {
        getline(in, s);
        sTotal ++;	
    }

    REQUIRE(sTotal == 14);
    compareFiles("tests/expected_2cycle_test_path.txt", "test_2cycle_path.txt");
    compareFiles("tests/expected_2cycle_test_edges.txt", "test_2cycle_edges.txt");
}