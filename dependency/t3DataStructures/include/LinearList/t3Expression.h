#ifndef T3_EXPRESSION_H
#define T3_EXPRESSION_H

#include <string>
#include <LinearList/t3Stack.h>

enum t3Precedence
{
    lparen,
    rparen,
    plus,
    minus,
    times,
    divide,
    mod,
    eos,
    operand
};

class t3Expression
{
public:
    t3Expression();
    
    // 给出中缀表达式
    void create(std::string s);
    
    void toPostfix();
    
    int evaluate();
    
    t3Precedence getToken(int n);
    
    const char getChar(int n);
    
    const char getSymbol(t3Precedence p);
    
    void printToken(t3Precedence p);
    
    std::string exp;
    
    t3Stack<t3Precedence> postfixStack;
    t3Stack<int> valueStack;
};

#endif
