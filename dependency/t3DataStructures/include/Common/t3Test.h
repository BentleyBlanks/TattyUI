#ifndef T3_TEST_H
#define T3_TEST_H

#include <iostream>
#include <string>

#define t3PrintError(errorMessage) t3PrintError_<int>(std::string(__FUNCTION__), errorMessage)

#define t3PrintErrorArg(argName, arg, errorMessage) t3PrintError_(std::string(__FUNCTION__), argName, arg, errorMessage)


template<class T>
void t3PrintError_(std::string functionName, std::string argName, T arg, std::string errorMessage)
{
    std::cout << "Error: " << "执行函数: " << functionName << "()时参数：" << argName << " = " << arg << "发生错误：" << errorMessage
    << std::endl;
}

template<class T>
void t3PrintError_(std::string functionName, std::string errorMessage)
{
    std::cout << "Error: " << "执行函数: " << functionName << "()时发生错误：" << errorMessage << std::endl;
}

void t3Log(const char* _Format,...);

//double t3GetRealTime();

#endif
