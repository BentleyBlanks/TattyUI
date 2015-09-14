#ifndef T3_STRINGADT_H
#define T3_STRINGADT_H

#include <stdio.h>

class t3StringADT
{
public:
    t3StringADT();
    t3StringADT(char* c);
    
    // 可重复构造
    void create(char* c);
    
    void setPattern(char* pattern);
    
    // 在当前字符串中寻找指定模式
    int find();
    
    // KMP算法
    int findFast();
    
    
private:
//    enum ERROR_STRING
//    {
//        T3_PATTERN_NULL = 0,
//        T3_STRING_NULL,
//    };
//    
//    void error(ERROR_STRING errorMessage);
    
    // 代匹配字符串
    char* string;
    
    char* pattern;
    
    //失配数组
    int *next;
    
    // 字符串长度
    int lengthString;
    
    int lengthPattern;
};


#endif
