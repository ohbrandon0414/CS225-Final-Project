#include "degree.h"
#include "bfs.h"

int main(int argc, const char** argv)
{
    // if (argc == 0) {
        BFS bfs("test.txt");
        bfs.printResult();
    // } else {
    //     for (int i = 0; i < argc; ++i) {
    //         BFS bfs(argv[i]);
    //         bfs.printResult();
    //     }
    // }
}