#include "../cs225/catch/catch.hpp"
#include "../degree.h"
#include "../bfs.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <locale>

using std::ifstream;
using std::stringstream;

// https://stackoverflow.com/a/217605
// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

bool tree_equals_output(stringstream & s, string filename)
{
    ifstream file(filename);
    string soln_s;
    string out_s;

    while(getline(file, soln_s))
    {
        if(!getline(s, out_s))
            return false;

        rtrim(soln_s);
        rtrim(out_s);

        if(out_s != soln_s)
            return false;
    }
    if(getline(s, soln_s))
        return false;

    return true;
}

void compareBinaryFiles( string yourFile, string ourFile ) 
{
    ifstream ourBinary( ourFile, std::ios::binary );
    stringstream ours;
    ours << ourBinary.rdbuf();

    if(!tree_equals_output(ours, yourFile))
        FAIL( "Your output in \"" + yourFile + "\" does not match our output in \"" + ourFile + "\"");
}

TEST_CASE("3 node graph", "[bfs]") {
    BFS bfs("tests/3node_test.txt");
    bfs.saveResult("test_3node_path.txt", "test_3node_edges.txt");
    compareBinaryFiles("expected_3node_test_path.txt", "test_3node_path.txt");
}