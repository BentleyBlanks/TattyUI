#ifndef T3_DATASTRUCTURESSETTINGS_H
#define T3_DATASTRUCTURESSETTINGS_H

#if defined( __WIN32__ ) || defined( _WIN32 )
    #define T3_PLATFORM_WIN32
#elif defined( __APPLE_CC__)
    #include <TargetConditionals.h>

    #if (T3_PLATFORM_OS_IPHONE_SIMULATOR) || (T3_PLATFORM_OS_IPHONE) || (T3_PLATFORM_IPHONE)
        #define T3_PLATFORM_OF_IPHONE
        #define T3_PLATFORM_OF_IOS
        #define T3_PLATFORM_OPENGLES
    #else
        #define T3_PLATFORM_OSX
    #endif

#elif defined (__ANDROID__)
    #define T3_PLATFORM_ANDROID
    #define T3_PLATFORM_OPENGLES

#elif defined(__ARMEL__)
    #define T3_PLATFORM_LINUX
    #define T3_PLATFORM_OPENGLES

#define T3_PLATFORM_LINUX_ARM
    #else
    #define T3_PLATFORM_LINUX
#endif

// 线性表默认长度
#define T3_STACK_DEFAULT_LENGTH 32
#define T3_QUEUE_DEFAULT_LENGTH 32

// 二叉树默认最大元素存放量
#define T3_BINARTTREE_DEFAULT_LENGTH 16
// 临时变量最大空间长度
#define T3_BINARTTREE_MAPINDEX_LENGTH 64

// 最大堆的最大容量
#define T3_HEAP_DEFAULT_LENGTH 100
#endif
