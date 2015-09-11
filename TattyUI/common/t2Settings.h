#ifndef TATTYUI_SETTINGS_H
#define TATTYUI_SETTINGS_H

#include <stdint.h>

// 平台宏
// 宏定义借鉴于:
// http://www.ogre3d.org/docs/api/html/OgrePlatform_8h-source.html
// OpenFrameworks->ofConstants.h宏定义

#if defined( __WIN32__ ) || defined( _WIN32 )
#define T2_PLATFORM_WINDOWS

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

// OpenGL
// glew使得不支持openGL的Windows得以使用OpenGL的高级特性
#define GLEW_STATIC
#include <glew.h>
#include <wglew.h>

#define WIN32_LEAN_AND_MEAN
// --!函数模板中的max与Visual C++中的全局的宏max冲突
// --!http://stackoverflow.com/questions/1904635/warning-c4003-and-errors-c2589-and-c2059-on-x-stdnumeric-limitsintmax
//#define NOMINMAX

//#include <glu.h>
#include <Windows.h>
#include <cstdlib>


// Apple平台
#elif defined( __APPLE_CC__)
#include <TargetConditionals.h>

// iOS支持 并没有iPad出现
#if (TARGET_OS_IPHONE_SIMULATOR) || (TARGET_OS_IPHONE) || (TARGET_IPHONE)
#define T2_PLATFORM_IPHONE
#define T2_PLATFORM_IOS
#define T2_PLATFORM_OPENGLES

// Mac平台的支持
#else
#define T2_PLATFORM_OSX
#endif

// Android平台的支持
#elif defined (__ANDROID__)
#define T2_PLATFORM_ANDROID
#define T2_PLATFORM_OPENGLES

// Linux平台的支持
#elif defined(__ARMEL__)
#define T2_PLATFORM_LINUX
#define T2_PLATFORM_OPENGLES
#define T2_PLATFORM_LINUX_ARM
#else
#define T2_PLATFORM_LINUX
#endif

// 渲染平台选择
#define T2_RENDERER_NANOVG

// nanovg
// 移动平台使用 gles2, 桌面平台使用gl2
#if (T2_PLATFORM_IOS || T2_PLATFORM_ANDROID)
#define NANOVG_GLES2_IMPLEMENTATION
#else
#define NANOVG_GL3_IMPLEMENTATION
#endif

// 无名div
#define T2_UNKNOWNNAME_DIV "TattyUI-unknownname-div-fengfenghuohuoxiangqianzou"

#define T2_EXIT(value) std::exit(value);

#define PI 3.1415926535897

#include <iostream>
// 实现cout << string 不包含则报错
#include <string>
#include <vector>
#include <stdint.h>
#include <stdlib.h>
// 包含min&max函数
#include <algorithm>
#include <assert.h>
#include <math.h>

// 暂不启用
typedef signed char	int8;
typedef signed short int16;
typedef signed int int32;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint;
#ifdef WIN32
typedef __int64 int64;
typedef unsigned __int64 uint64;
#endif
typedef float float32;
typedef double float64;

using namespace std;

// log借鉴于box2d的b2Log
void t2Log(const char* string, ...);

#define t2PrintError(errorMessage) t2PrintError_<int>(std::string(__FUNCTION__), errorMessage)

#define t2PrintErrorArg(argName, arg, errorMessage) t3PrintError_(std::string(__FUNCTION__), argName, arg, errorMessage)

template<class T>
void t2PrintError_(std::string functionName, std::string argName, T arg, std::string errorMessage)
{
    std::cout << "Error: " << "执行函数: " << functionName << "()时参数：" << argName << " = " << arg << "发生错误：" << errorMessage
        << std::endl;
}

template<class T>
void t2PrintError_(std::string functionName, std::string errorMessage)
{
    std::cout << "Error: " << "执行函数: " << functionName << "()时发生错误：" << errorMessage << std::endl;
}

// 枚举常量
enum t2WindowMode
{
	T2_WINDOW_WINDOWED = 0, // 窗口化
	T2_WINDOW_NOTITLE,	// 无标题栏设计
	T2_WINDOW_FULLSCREEN, // 全屏
	T2_WINDOW_GAMEMODE // 特别优化后的全屏游戏模式
};

enum t2FillMode
{
	T2_OUTLINE = 0,
	T2_FILLED = 1,
};


enum t2BlendMode
{
	T2_BLENDMODE_ALPHA = 0,
	T2_BLENDMODE_DISABLED = 1,
	T2_BLENDMODE_ADD = 2,
	T2_BLENDMODE_MULTIPLY = 3,
	T2_BLENDMODE_SCREEN = 4,
	T2_BLENDMODE_SUBTRACT = 5,
};

// font
enum t2FontSize
{
	T2_FONT_DEFAULT = 10,
	T2_FONT_SMALL = 5,
	T2_FONT_MIDDLE = 10,
	T2_FONT_LARGE = 20,
};

enum t2FontSpacing
{
	T2_FONT_SPACING_DEFAULT = 5,
	T2_FONT_SPACING_NEAR = 2, 
	T2_FONT_SPACING_FAR = 10,
};

#define STRINGIFY(x) #x

// roundrect
// 0.5 * PI 推荐的边界半径与resolution之间的比率转换
#define T2_RATIO_RADIUS_TO_SEGMENTS 1.5707963267948f

// 默认的字体路径
#define T2_DEFAULT_FONTPATH "../resources/font/msyh.ttf"
#define T2_MAX_CLASSNAME_LENGTH 256
#define T2_MAX_NAME_LENGTH 48
#define T2_MAX_TEXT_LENGTH 2048
#define T2_MAX_PATH_LENGTH 256
#define T2_MAX_XMLSTRING_LENGTH 128

// math
#ifndef T2_DEGREE_TO_RADIAN
#define T2_DEGREE_TO_RADIAN (PI/180.0f)
#endif

#ifndef T2_RADIAN_TO_DEGREE
#define T2_RADIAN_TO_DEGREE (180.0f/PI)
#endif

// 浮点数判断容差
#define T2_TOLERANCE_INT 0
#define T2_TOLERANCE_float 0.000001f
#define T2_TOLERANCE_FLOAT64 0.00000001

// event
// 按键与GLFW完全兼容
#define T2_KEY_UNKNOWN            -1

/* Printable keys */
#define T2_KEY_SPACE              32
#define T2_KEY_APOSTROPHE         39  /* ' */
#define T2_KEY_COMMA              44  /* , */
#define T2_KEY_MINUS              45  /* - */
#define T2_KEY_PERIOD             46  /* . */
#define T2_KEY_SLASH              47  /* / */
#define T2_KEY_0                  48
#define T2_KEY_1                  49
#define T2_KEY_2                  50
#define T2_KEY_3                  51
#define T2_KEY_4                  52
#define T2_KEY_5                  53
#define T2_KEY_6                  54
#define T2_KEY_7                  55
#define T2_KEY_8                  56
#define T2_KEY_9                  57
#define T2_KEY_SEMICOLON          59  /* ; */
#define T2_KEY_EQUAL              61  /* = */
#define T2_KEY_A                  65
#define T2_KEY_B                  66
#define T2_KEY_C                  67
#define T2_KEY_D                  68
#define T2_KEY_E                  69
#define T2_KEY_F                  70
#define T2_KEY_G                  71
#define T2_KEY_H                  72
#define T2_KEY_I                  73
#define T2_KEY_J                  74
#define T2_KEY_K                  75
#define T2_KEY_L                  76
#define T2_KEY_M                  77
#define T2_KEY_N                  78
#define T2_KEY_O                  79
#define T2_KEY_P                  80
#define T2_KEY_Q                  81
#define T2_KEY_R                  82
#define T2_KEY_S                  83
#define T2_KEY_T                  84
#define T2_KEY_U                  85
#define T2_KEY_V                  86
#define T2_KEY_W                  87
#define T2_KEY_X                  88
#define T2_KEY_Y                  89
#define T2_KEY_Z                  90
#define T2_KEY_LEFT_BRACKET       91  /* [ */
#define T2_KEY_BACKSLASH          92  /* \ */
#define T2_KEY_RIGHT_BRACKET      93  /* ] */
#define T2_KEY_GRAVE_ACCENT       96  /* ` */
#define T2_KEY_WORLD_1            161 /* non-US #1 */
#define T2_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define T2_KEY_ESCAPE             256
#define T2_KEY_ENTER              257
#define T2_KEY_TAB                258
#define T2_KEY_BACKSPACE          259
#define T2_KEY_INSERT             260
#define T2_KEY_DELETE             261
#define T2_KEY_RIGHT              262
#define T2_KEY_LEFT               263
#define T2_KEY_DOWN               264
#define T2_KEY_UP                 265
#define T2_KEY_PAGE_UP            266
#define T2_KEY_PAGE_DOWN          267
#define T2_KEY_HOME               268
#define T2_KEY_END                269
#define T2_KEY_CAPS_LOCK          280
#define T2_KEY_SCROLL_LOCK        281
#define T2_KEY_NUM_LOCK           282
#define T2_KEY_PRINT_SCREEN       283
#define T2_KEY_PAUSE              284
#define T2_KEY_F1                 290
#define T2_KEY_F2                 291
#define T2_KEY_F3                 292
#define T2_KEY_F4                 293
#define T2_KEY_F5                 294
#define T2_KEY_F6                 295
#define T2_KEY_F7                 296
#define T2_KEY_F8                 297
#define T2_KEY_F9                 298
#define T2_KEY_F10                299
#define T2_KEY_F11                300
#define T2_KEY_F12                301
#define T2_KEY_F13                302
#define T2_KEY_F14                303
#define T2_KEY_F15                304
#define T2_KEY_F16                305
#define T2_KEY_F17                306
#define T2_KEY_F18                307
#define T2_KEY_F19                308
#define T2_KEY_F20                309
#define T2_KEY_F21                310
#define T2_KEY_F22                311
#define T2_KEY_F23                312
#define T2_KEY_F24                313
#define T2_KEY_F25                314
#define T2_KEY_KP_0               320
#define T2_KEY_KP_1               321
#define T2_KEY_KP_2               322
#define T2_KEY_KP_3               323
#define T2_KEY_KP_4               324
#define T2_KEY_KP_5               325
#define T2_KEY_KP_6               326
#define T2_KEY_KP_7               327
#define T2_KEY_KP_8               328
#define T2_KEY_KP_9               329
#define T2_KEY_KP_DECIMAL         330
#define T2_KEY_KP_DIVIDE          331
#define T2_KEY_KP_MULTIPLY        332
#define T2_KEY_KP_SUBTRACT        333
#define T2_KEY_KP_ADD             334
#define T2_KEY_KP_ENTER           335
#define T2_KEY_KP_EQUAL           336
#define T2_KEY_LEFT_SHIFT         340
#define T2_KEY_LEFT_CONTROL       341
#define T2_KEY_LEFT_ALT           342
#define T2_KEY_LEFT_SUPER         343
#define T2_KEY_RIGHT_SHIFT        344
#define T2_KEY_RIGHT_CONTROL      345
#define T2_KEY_RIGHT_ALT          346
#define T2_KEY_RIGHT_SUPER        347
#define T2_KEY_MENU               348
#define T2_KEY_LAST               T2_KEY_MENU


// mouse
#define T2_MOUSE_BUTTON_1         0
#define T2_MOUSE_BUTTON_2         1
#define T2_MOUSE_BUTTON_3         2
#define T2_MOUSE_BUTTON_4         3
#define T2_MOUSE_BUTTON_5         4
#define T2_MOUSE_BUTTON_6         5
#define T2_MOUSE_BUTTON_7         6
#define T2_MOUSE_BUTTON_8         7
#define T2_MOUSE_BUTTON_LAST      T2_MOUSE_BUTTON_8
#define T2_MOUSE_BUTTON_LEFT      T2_MOUSE_BUTTON_1
#define T2_MOUSE_BUTTON_RIGHT     T2_MOUSE_BUTTON_2
#define T2_MOUSE_BUTTON_MIDDLE    T2_MOUSE_BUTTON_3

// Floekr2d版本信息
// --!来自box2d http://en.wikipedia.org/wiki/Software_versioning
struct t2Version
{
	int major;		///< significant changes
	int minor;		///< incremental changes
	int revision;		///< bug fixes

	void print()
	{
		std::cout << "TattyUI版本:" << major << "." << minor << "." << revision << std::endl;
	}
};

#ifdef T2_PLATFORM_WINDOWS
// --!OSX下自带该函数 并不清楚Win32为何没有
int strcasecmp(const char *a, const char *b);
#endif

// 公共API
void t2SetWindowWidth(int width);

void t2SetWindowHeight(int height);

int t2GetWindowWidth();

int t2GetWindowHeight();

// OpenGL预定义版本
// Windows下无需设定OpenGL版本(glew自动配置)
int t2GetGLVersionMajor();

int t2GetGLVersionMinor();

void t2SetGLVersionMajor(int major);

void t2SetGLVersionMinor(int minor);

// 当前版本号
extern t2Version tattyVersion;

#endif