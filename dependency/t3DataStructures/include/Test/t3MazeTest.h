#include <LinearList/t3Maze.h>

#include <Common/t3Test.h>
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    t3Maze maze(7, 6);
    
    maze << 1,  1, 1, 1, 1, 1,
    
            1,  0, 0, 0, 0, 1,
            1,  1, 1, 1, 0, 1,
            1,  0, 0, 1, 0, 1,
            1,  0, 0, 1, 0, 1,
            1,  0, 0, 0, 0, 1,
    
            1,  1, 1, 1, 1, 1;
    
    maze.print();
    
    maze.path(3, 1);

    getchar();
    return 0;
}