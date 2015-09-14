#define _CRT_SECURE_NO_WARNINGS
#include "t3StringADT.h"
#include <string.h>
#include <Common/t3Test.h>

t3StringADT::t3StringADT()
{
    lengthString = 0;
    lengthPattern = 0;
    string = NULL;
    pattern = NULL;
}

t3StringADT::t3StringADT(char* c)
{
    create(c);
    
    lengthPattern = 0;
    pattern = NULL;
}

void t3StringADT::create(char *c)
{
    if(!c)
    {
        t3PrintError("代匹配String字符串不能为空");
        lengthString = 0;
        lengthPattern = 0;
        string = NULL;
        pattern = NULL;
        
        return;
    }
    
    // 已构造 需重定向内存
    if(string != NULL)
    {
        delete string;
        lengthString = 0;
        string = NULL;
    }
    
    lengthString = strlen(c);
    
    string = new char[lengthString]();
    strcpy(string, c);
    
    t3Log("t3StringADT: lengthString:%d, string:%s\n", lengthString, string);
}

void t3StringADT::setPattern(char* p)
{
    if(!p)
    {
        t3PrintError("代匹配Pattern字符串不能为空");
        return;
    }
    
    // 已构造 需重定向内存
    if(pattern != NULL)
    {
        delete pattern;
        lengthPattern = 0;
        pattern = NULL;
    }

    lengthPattern = strlen(p);
    
    pattern = new char[lengthPattern]();
    strcpy(pattern, p);
    
    t3Log("t3StringADT: lengthPattern:%d, pattern:%s\n", lengthPattern, pattern);
    
    // 失配数组分配内存
    if(next != NULL)
    {
        delete next;
        next = NULL;
    }
    
    next = new int[lengthPattern]();
    //t3Log("%d", sizeof(next));
//    
//    memset(next, -1, sizeof(next));
//    for(int i=0; i<lengthPattern; i++)
//        t3Log("%d", next[i]);
}

// 在当前字符串中寻找指定模式
int t3StringADT::find()
{
    if(!pattern && lengthPattern > 0)
    {
        t3PrintError("Pattern字符串不能为空，请先setPattern()指定模式字符串");
        return -1;
    }
    
    int i = 0, j = 0;
    // pattern/string末尾下标
    int lastPattern = lengthPattern-1, lastString = lengthString-1;
    // 当前循环代匹配字符下标 / 距离end长度为lengthPattern的起始下标
    int endMatch = lastPattern, startMatch = 0;
    
    for(; endMatch < lastString; endMatch++, startMatch++)
    {
        // 末位匹配
        if(string[endMatch] == pattern[lastPattern])
            // core
            for(j = 0, i = startMatch; j<lastPattern && string[i] == pattern[j]; i++, j++);
        
        if(j == lastPattern)
            return startMatch;
    }
    
    return -1;
}

int t3StringADT::findFast()
{
    if(!pattern && lengthPattern > 0)
    {
        t3PrintError("Pattern字符串不能为空，请先setPattern()指定模式字符串");
        return -1;
    }
    
    // next数组初始化求值
    next[0] = -1;
    for(int j = 1, i = 0; j<lengthPattern; j++)
    {
        // 上一字符next值
        i = next[j-1];
        
        // 可否根福上一next值来递推到对应前缀的下一字符
        while(pattern[j] != pattern[i+1] && i >= 0)
            // 无法递推 相当于自身与自身KMP匹配 回溯到上一可能位置
            i = next[i];
        
        if(pattern[j] == pattern[i+1])
            // 从上一结果直接递推
            next[j] = i+1;
        else
            next[j] = -1;
    }
    
    // 实际匹配
    int i = 0, j = 0;
    while(i<lengthString && j<lengthPattern)
    {
        if(string[i] == pattern[j])
        {
            i++;
            j++;
        }
        else if(j == 0)
            // 可直接跳过此字符到下一位置
            i++;
        else
            j = next[j-1]+1;
    }
    
    // 匹配成功i多前进了lengthPattern长度
    return ((j == lengthPattern) ? (i-lengthPattern) : -1);
}