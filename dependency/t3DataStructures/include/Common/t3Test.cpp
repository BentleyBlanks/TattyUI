#include <Common/t3Test.h>
#include <Common/t3DataStructuresSettings.h>
#include <stddef.h>
#include <assert.h>
#include <float.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
//template<class T>
//void t3PrintError_(std::string functionName, std::string argName, T arg, std::string errorMessage)
//{ 
//    std::cout << "Error: " << "执行函数: " << functionName << "()时参数：" << argName << " = " << arg << "发生错误：" << errorMessage << std::endl;
//}
//
//void t3PrintError_(std::string functionName, std::string errorMessage)
//{
//    std::cout << "Error: " << "执行函数: " << functionName << "()时发生错误：" << errorMessage << std::endl;
//}

void t3Log(const char * _Format,...)
{
    va_list args;
    va_start(args,_Format);
    
    FILE* out = stdout;
    vfprintf(out, _Format, args);
    fprintf(out, "\n");
    
    va_end( args );
}
