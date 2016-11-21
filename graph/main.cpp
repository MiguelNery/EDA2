#include <iostream>
#include "maze.cpp"


int main() {

    maze::setup();

    int numcells = maze::NumCells;

    unsigned short *maze = new unsigned short[numcells * numcells];
    memset(maze, 0, (numcells * numcells) * sizeof(unsigned short));
    // render maze on bitmap
    maze::compute_maze(maze);

    for (int i = 0; i < numcells * numcells; ++i) {
        if (!(i % numcells)) {
            printf("\n");
        }
        printf("%d ", maze[i]);
    }
    printf("\n");
    // cleanup
    delete[](maze);

    return 0;
}
