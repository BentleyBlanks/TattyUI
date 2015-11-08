#include <TattyUI/common/t2Settings.h>
#include <stddef.h>
#include <assert.h>
#include <float.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <strstream>
// titleBar支持
#include <TattyUI/common/t2Window.h>

// --！重大革新:小改动:BUG修复
t2Version tattyVersion = { 0, 0, 9 };

// 注意:只能在Debug模式下才能使用
void t2Log(const char* string, ...)
{
#ifdef _DEBUG
	va_list args;
	va_start(args, string);
	vprintf(string, args);
	va_end(args);
#endif
}

#ifdef T2_PLATFORM_WINDOWS
int strcasecmp(const char *a, const char *b)
{
	char ca, cb;
	do
	{
		ca = *a++;
		cb = *b++;
		ca = tolower(ca);
		cb = tolower(cb);
	} while((ca == cb) && (ca));
	return (int)ca - cb;
}
#endif

std::string getDivGlobalID()
{
    static int id = 0;

    std::strstream ss;
    std::string s = "TattyUI_Global_Div_ID_", num;
    ss << id++;
    ss >> num;
    s += num;

    return s;
}

std::string getRootDivGlobalID()
{
    return string("TattyUI_Global_Div_ID_ROOT");
}

static int t2WindowWidth = 0, t2WindowHeight = 0;

void t2SetWindowWidth(int width)
{
	t2WindowWidth = width;
}

void t2SetWindowHeight(int height)
{
	t2WindowHeight = height;
}

int t2GetWindowWidth()
{
    return t2WindowWidth;
}

int t2GetWindowHeight()
{
    return t2WindowHeight;
}

int glVersionMinor = 4, glVersionMajor = 4;

int t2GetGLVersionMajor() 
{
    return glVersionMajor;
}

int t2GetGLVersionMinor() 
{
    return glVersionMinor;
}

void t2SetGLVersionMajor(int major) 
{
    glVersionMajor = major;
}

void t2SetGLVersionMinor(int minor) 
{
    glVersionMinor = minor;
}

void t2SetWindowTitleBarHeight(int height)
{
    TattyUI::t2Window::getInstance()->setTitleBarHeight(height);
}

int t2GetWindowTitleBarHeight()
{
    return TattyUI::t2Window::getInstance()->getTitleBarHeight();
}
