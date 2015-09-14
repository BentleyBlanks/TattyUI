#ifndef T3_MAZE_H
#define T3_MAZE_H

#include<iostream>
#include <LinearList/t3Stack.h>

class t3Maze//:public std::ostream
{
public:
    t3Maze(int row, int col);
    
    ~t3Maze();
    
    void print();
    
    void add(int value);
    
    // 给定出口
    void path(int exitRow, int exitCol);
    
    t3Maze& operator,(int value);
    
    t3Maze& operator<<(int value);
    
    int col, row;
    
    int **m;
    
    int pCol, pRow;
};
#endif