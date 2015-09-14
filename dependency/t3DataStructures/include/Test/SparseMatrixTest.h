#include <SparseMatrix/t3SparseMatrixADT.h>
#include <Common/t3Test.h>
#include <Common/t3Timer.h>

int main(int argc, char* argv[])
{
    t3SparseMatrixADT m1, *m2 = NULL;
    t3Timer timer;
    
    m1.create(6, 6, 8);
    
    // 强行默认是按行顺序排列了的
    m1.add(0, 0, 15);
    m1.add(0, 3, 22);
    m1.add(0, 5, -15);
    m1.add(1, 1, 11);
    m1.add(1, 2, 3);
    m1.add(2, 3, -6);
    m1.add(4, 0, 91);
    m1.add(5, 2, 28);
    
    m1.print();
    
    timer.start();
    for(int i=0; i<500000; i++)
    {
        m2 = m1.transpose();
    }
    timer.end();
    
    t3Log("transpose()花费时间: %lf\n", timer.difference());
    
    
    timer.start();
    for(int i=0; i<500000; i++)
    {
        m2 = m1.transposeFast();
    }
    timer.end();
    
    t3Log("transposeFast()花费时间: %lf\n", timer.difference());
    
    m2->print();
    
    getchar();

    return 0;
}