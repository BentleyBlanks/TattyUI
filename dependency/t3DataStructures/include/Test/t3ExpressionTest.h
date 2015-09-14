#include <LinearList/t3Expression.h>

#include <Common/t3Test.h>
#include <iostream>
#include <string>

//#define T3_TEST_POSTFIX
#define T3_TEST_INFIX_TO_POSTFIX

int main(int argc, char* argv[])
{
    t3Expression exp;
    
#ifdef T3_TEST_POSTFIX
    exp.create("42/1-12*+22*- ");
    
    t3Log("Expression evaluate: %d", exp.evaluate());
#endif
    
#ifdef T3_TEST_INFIX_TO_POSTFIX
    exp.create("((((4/2)-1)+(1*2))-(2*2)) ");
    
    exp.toPostfix();
    
    t3Log("Expression evaluate: %d", exp.evaluate());
#endif
    getchar();
    return 0;
}