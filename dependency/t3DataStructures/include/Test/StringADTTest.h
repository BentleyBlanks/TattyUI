#include <String/t3StringADT.h>
#include <Common/t3Test.h>
#include <Common/t3Timer.h>

int main(int argc, char* argv[])
{
    t3Timer timer;
    
    t3StringADT s;
    s.create("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa ababababababababababababababababab aab");
    
    s.setPattern("aab");
    
    timer.start();
    for(int i=0; i<1000000; i++)
        s.find();
    timer.end();
    t3Log("find()花费时间: %lf\n", timer.difference());
    
    t3Log("-----------------------\n");
    
    timer.start();
    for(int i=0; i<1000000; i++)
        s.findFast();
    timer.end();
    
    t3Log("findFast()花费时间: %lf\n", timer.difference());

    //s.findFast("lao");
    getchar();
    return 0;
}