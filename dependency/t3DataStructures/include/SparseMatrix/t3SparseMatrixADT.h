#ifndef T3_SPARSEMATRIXADT_H
#define T3_SPARSEMATRIXADT_H

class term
{
public:
    term():col(0), row(0), value(0){}
    
    term(int row, int col, int value):col(col), row(row), value(value){}
    
    int col, row;
    int value;
};

// 数组构造成的稀疏矩阵
class t3SparseMatrixADT
{
public:
    // 创建一个最大能容纳maxRow x maxCol 非零元素个数count的稀疏矩阵 本质上是一维矩阵
    void create(int maxRow, int maxCol, int itemCount);
    
    // 返回一个堆中分配的稀疏矩阵
    t3SparseMatrixADT* transpose();
    
    t3SparseMatrixADT* transposeFast();
    
    // 在矩阵中添加一项<row, col, value>的拷贝
    void add(int row, int col, int value);
    
    void add(term& t);
    
    void print();
    
    void operator+(t3SparseMatrixADT& m);
    
    void operator*(t3SparseMatrixADT& m);
    
    term *m;
    
    // 非零元素个数
    int count;
};


#endif
