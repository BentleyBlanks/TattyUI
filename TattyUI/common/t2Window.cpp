#include <TattyUI/common/t2Window.h>
#include <TattyUI/common/t2Settings.h>

#include <TattyUI/controller/event/t2EventController.h>

#define GLFW_INCLUDE_NONE

#if (_MSC_VER)
#include <glfw3.h>

#ifdef T2_PLATFORM_WINDOWS
#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
// 倘若需要获得各个不同平台的窗口句柄 需要用到以下头文件
// --!摘自 http://www.glfw.org/docs/latest/glfw3native_8h.html
#include <glfw3native.h>
#endif

#else
#include "glfw3.h"
#endif

#include <TattyUI/common/t2Rect.h>
#include <TattyUI/common/t2Matrix4.h>

// 窗口指针
// --!不允许放置在命名空间中 
static GLFWwindow* glfwWindow = NULL;

static float64 mouseX = 0, mouseY = 0;
// 上一帧鼠标位置
static float64 pmouseX = 0, pmouseY = 0;

// 回调函数前向声明
void mouse_cb(GLFWwindow* windowP_, int button, int state, int mods);
void cursorpos_cb(GLFWwindow* windowP_, double x, double y);
void keyboard_cb(GLFWwindow* windowP_, int key, int scancode, int action, int mods);
void resize_cb(GLFWwindow* windowP_, int w, int h);
void exit_cb(GLFWwindow* windowP_);
void scroll_cb(GLFWwindow* windowP_, double x, double y);
void drop_cb(GLFWwindow* windowP_, const char* dropString);
void error_cb(int errorCode, const char* errorDescription);

namespace TattyUI
{
	t2Window::t2Window()
	{
		// 挂钩错误处理回调函数
		glfwSetErrorCallback(error_cb);
	}

	void t2Window::setup(int width, int height)
	{
		if (!glfwInit())
		{
			cout << "t2Window:" << "无法初始化 glfw" << endl;
			return;
		}

        // 配置OpenGL版本
        // --!Mac下某些机型上的OSX只支持到OpenGL 3.x 那么可以在t2Window.setup之前定义glversionMajor与glVersionMinor
        // --!这两个公共API都在t2Settings中声明
#ifdef T2_PLATFORM_OSX
        // Windows下的Glew自动配置opengl最高版本
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, t2GetGLVersionMajor());
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, t2GetGLVersionMinor());
        if(t2GetGLVersionMajor() >= 3)
        {
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        }
#endif

		// --!配置OpenGL的图形设置 如颜色深度 抗锯齿倍数应该在图形驱动中初始化完成 此处先集成在窗口中
        // --!未来实现方式类似于driver->init();

        // 默认八倍抗锯齿 
        glfwWindowHint(GLFW_SAMPLES, 8);
        glfwWindowHint(GLFW_RED_BITS, 8);
        glfwWindowHint(GLFW_GREEN_BITS, 8);
        glfwWindowHint(GLFW_BLUE_BITS, 8);
        glfwWindowHint(GLFW_ALPHA_BITS, 8);
        glfwWindowHint(GLFW_STENCIL_BITS, 8);
        glfwWindowHint(GLFW_DEPTH_BITS, 24);

		// 支持跨显示器全屏模式即为游戏模式
		if (mode == T2_WINDOW_GAMEMODE)
		{
			int monitorCount;
			GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);
			if (monitorCount > 0)
			{
				//在首要使用的屏幕上全屏 相当于glfwGetPrimaryMonitor
				glfwWindow = glfwCreateWindow(width, height, "", monitors[0], NULL);
			}
			else
			{
				cout << "t2Window:" << "无法找到任何显示器" << endl;
			}
		}
		else
		{
			if (mode == T2_WINDOW_NOTITLE)
			{
				glfwWindow = glfwCreateWindow(width, height, "", NULL, NULL);
				if (!glfwWindow)
				{
					cout << "t2Window:" << "无法创建glfw窗口" << endl;
				}

				HWND hwnd = glfwGetWin32Window(glfwWindow);
				// 无边框/可调节框
				// --!http://msdn.microsoft.com/en-us/library/windows/desktop/ms632600(v=vs.85).aspx
				// WS_THICKFRAME = WS_SIZEBOX 专用于调节窗口大小
                if(resizable)
                {
                    SetWindowLong(hwnd, GWL_STYLE, WS_OVERLAPPED | WS_THICKFRAME | WS_SYSMENU);
                }
                else
                {
                    SetWindowLong(hwnd, GWL_STYLE, WS_POPUP);
                    SetWindowLong(hwnd, GWL_EXSTYLE, 0);
                    //SetWindowLong(hwnd, GWL_STYLE, WS_OVERLAPPED | WS_SYSMENU);
                }

				SetWindowPos(hwnd, HWND_TOP, position.x, position.y, width, height, SWP_FRAMECHANGED | SWP_SHOWWINDOW);
			}
			else
			{
				glfwWindow = glfwCreateWindow(width, height, "", NULL, NULL);
				if (!glfwWindow)
				{
					cout << "t2Window:" << "无法创建glfw窗口" << endl;
				}

				// 不可调节窗口大小
				if (!resizable)
				{
					HWND hwnd = glfwGetWin32Window(glfwWindow);
					//// 参考于#9:http://bbs.csdn.net/topics/10096949
					//// 无法禁止最大化按钮
					//DWORD style = GetWindowLong(hwnd, GWL_STYLE);
					//style = style & (~WS_THICKFRAME) | WS_DLGFRAME;
					//SetWindowLong(hwnd, GWL_STYLE, style);

					// 参考于:http://stackoverflow.com/questions/3275989/disable-window-resizing-win32
					// 禁止最大化图标防止变化窗口大小 与标准只少了一个WS_THICKFRAME
					SetWindowLong(hwnd, GWL_STYLE, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX);
					SetWindowPos(hwnd, HWND_TOP, position.x, position.y, width, height, SWP_FRAMECHANGED | SWP_SHOWWINDOW);
				}

				if (mode == T2_WINDOW_FULLSCREEN)
				{
					setFullScreen();
				}
			}
		}

		// 不直接设定this->width&height 而是创建了窗口后再次获取实际大小
		glfwGetWindowSize(glfwWindow, &this->width, &this->height);

		// Makes the context of the specified window current for the calling thread
		// --!摘自 http://www.glfw.org/docs/latest/group__context.html
		glfwMakeContextCurrent(glfwWindow);

        // --!完成GLFW的配置工作 预备配置GLEW
        // --!只要显卡支持1.5以上OpenGL glew都能很好的支持高级版本的gl函数
        initGlew();

        // 图形驱动的初始化阶段 清屏等等
        // --!设置为2D渲染模式
        set2d(width, height);
	}


	// getter/setter
	// --!get
	t2Point2i t2Window::getSize()
	{
		if (mode == T2_WINDOW_GAMEMODE)
		{
			const GLFWvidmode* desktopMode = glfwGetVideoMode(glfwGetWindowMonitor(glfwWindow));
			if (desktopMode)
				return t2Point2i(desktopMode->width, desktopMode->height);
			else
				return t2Point2i(width, height);
		}
		else
		{
			glfwGetWindowSize(glfwWindow, &width, &height);
			return t2Point2i(width, height);
		}
	}

	t2Point2i t2Window::getPosition()
	{
		glfwGetWindowPos(glfwWindow, &position.x, &position.y);
		return position;
	}

	int t2Window::getHeight()
	{
		return getSize().y;
	}

	int t2Window::getWidth()
	{
		return getSize().x;
	}

	bool t2Window::isVerticalSync()
	{
		return verticalSync;
	}

	int t2Window::getMode()
	{
		return mode;
	}

	t2Point2i t2Window::getScreenSize()
	{
		int count;
		GLFWmonitor** monitors = glfwGetMonitors(&count);

		if (count > 0)
		{
			int currentMonitor = getCurrentMonitor();
			const GLFWvidmode* desktopMode = glfwGetVideoMode(monitors[currentMonitor]);
			if (desktopMode)
				return t2Point2i(desktopMode->width, desktopMode->height);
			else
				return t2Point2i();
		}
		else
			return t2Point2i();
	}

	// --!set
	void t2Window::setPosition(int x, int y)
	{
		setPosition(t2Point2i(x, y));
	}

	void t2Window::setPosition(t2Point2i position)
	{
		this->position.clone(position);
		glfwSetWindowPos(glfwWindow, position.x, position.y);
	}

	void t2Window::setSize(int width, int height)
	{
		setSize(t2Point2i(width, height));
	}

	void t2Window::setSize(const t2Point2i size)
	{
		this->size.clone(size);
		glfwSetWindowSize(glfwWindow, size.x, size.y);

		// --!全局窗口大小
		t2SetWindowHeight(size.y);
		t2SetWindowWidth(size.x);
	}

	void t2Window::setResizable(bool resizable)
	{
		this->resizable = resizable;
	}

	void t2Window::setHeight(int height)
	{
		this->height = height;
		glfwSetWindowSize(glfwWindow, this->width, height);

		// --!全局窗口大小
		t2SetWindowHeight(height);
	}

	void t2Window::setWidth(int width)
	{
		this->width = height;
		glfwSetWindowSize(glfwWindow, width, this->height);

		// --!全局窗口大小
		t2SetWindowWidth(width);
	}

	void t2Window::setMode(int mode)
	{
		this->mode = mode;
	}

	void t2Window::setVeticalSync(bool verticalSync)
	{
		this->verticalSync = verticalSync;

		if (verticalSync)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
	}

	void t2Window::setTitle(std::string title)
	{
		this->title = title;
		glfwSetWindowTitle(glfwWindow, title.c_str());
	}

	void t2Window::setIcon()
	{
		// --!暂无图片支持
	}

	void t2Window::set2d(float width, float height)
	{
		//设置视区尺寸
		glViewport(0, 0, width, height);

        // --!无效
        ////重置坐标系统，使用投影变换复位
		//glMatrixMode(GL_PROJECTION);
		//glLoadIdentity();

		//glOrtho(0.0f, width, height, 0, 1.0f, -1.0f);

		//glMatrixMode(GL_MODELVIEW);
		//glLoadIdentity();

		// --!全局窗口大小
		t2SetWindowHeight(height);
		t2SetWindowWidth(width);
	}

	void t2Window::setFullScreen()
	{
		HWND hwnd = glfwGetWin32Window(glfwWindow);

		SetWindowLong(hwnd, GWL_EXSTYLE, 0);
		SetWindowLong(hwnd, GWL_STYLE, WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS);
		SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED | SWP_SHOWWINDOW);

		int fullscreenWidth = getScreenSize().x;
		int fullscreenHeight = getScreenSize().y;

		int monitorCount;
		// 得到当前显示器个数
		GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);

		for (int i = 0; i < monitorCount; i++)
		{
			const GLFWvidmode* desktopMode = glfwGetVideoMode(monitors[i]);

			//统计所有的显示器像素宽高 直接撑满整个显示器群
			fullscreenWidth += desktopMode->width;
			// 最大高度
			if (desktopMode->height > fullscreenHeight)
			{
				fullscreenHeight = desktopMode->height;
			}
		}

		int monitorX, monitorY;
		int currentMonitor = getCurrentMonitor();
		glfwGetMonitorPos(monitors[currentMonitor], &monitorX, &monitorY);

		SetWindowPos(hwnd, HWND_TOPMOST, monitorX, monitorY, fullscreenWidth, fullscreenHeight, SWP_SHOWWINDOW);
	}

	void t2Window::hideCursor(bool hide)
	{
		if (hide)
			glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		else
			glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	void t2Window::swapBuffer()
	{
		// 交换前后两缓冲 
		glfwSwapBuffers(glfwWindow);
	}

	void t2Window::processEvents()
	{
		// 挂钩好的回调会被更新 即如鼠标键盘的事件等等
		glfwPollEvents();
	}

	// 挂钩所有回调函数
	void t2Window::initCallBack()
	{
		if (!glfwWindow)
			return;

		glfwSetMouseButtonCallback(glfwWindow, mouse_cb);
		glfwSetCursorPosCallback(glfwWindow, cursorpos_cb);
		glfwSetKeyCallback(glfwWindow, keyboard_cb);
		glfwSetWindowSizeCallback(glfwWindow, resize_cb);
		glfwSetWindowCloseCallback(glfwWindow, exit_cb);
        glfwSetScrollCallback(glfwWindow, scroll_cb);

        // --!拖拽支持似乎只有OF独占 怀疑是OF自定义后的结果
		//glfwSetDropCallback(glfwWindow, drop_cb);
	}

	void t2Window::exit()
	{
		glfwTerminate();
	}

	// 获得当前焦点所在的窗口的序号
	int t2Window::getCurrentMonitor()
	{
		int monitorCount;
		GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);

		int windowX, windowY;
		glfwGetWindowPos(glfwWindow, &windowX, &windowY);

		for (int i = 0; i < monitorCount; i++)
		{
			// 当前显示屏的左上角位置
			int monitorX, monitorY;
			glfwGetMonitorPos(monitors[i], &monitorX, &monitorY);

			// 获取当前桌面属性元祖
			// --!不明为何要const前缀
			const GLFWvidmode* desktopMode = glfwGetVideoMode(monitors[i]);

			t2Rect moniotorRect(monitorX, monitorY, desktopMode->width, desktopMode->height);

			// 判定窗口左上角坐标是在那块显示屏中
			if (moniotorRect.inside(windowX, windowY))
			{
				return i;
				break;
			}
		}

		return 0;
	}

    bool t2Window::initGlew()
    {
        glewExperimental = GL_TRUE;
        GLenum err = glewInit();
        if(GLEW_OK != err)
        {
            /* Problem: glewInit failed, something is seriously wrong. */
            t2Log("t2Window: couldn't init GLEW: %s", glewGetErrorString(err));
            return false;
        }

        //glGetError();

        return true;
    }
}

// 临时代码
// mouse
void t2GetMousePos(float64 *x, float64 *y)
{
	glfwGetCursorPos(glfwWindow, x, y);
	mouseX = *x;
	mouseY = *y;
}

float64 t2GetMouseX()
{
	glfwGetCursorPos(glfwWindow, &mouseX, 0);
	return mouseX;
}

float64 t2GetMouseY()
{
	glfwGetCursorPos(glfwWindow, 0, &mouseY);
	return mouseY;
}

GLFWwindow* getGLFWWindow()
{
	return glfwWindow;
}

// callback
// --!借鉴自OpenFrameworks
static void mouse_cb(GLFWwindow* windowP_, int button, int state, int mods)
{
    TattyUI::t2EventController* driver = TattyUI::t2EventController::getInstance();

    pmouseX = mouseX;
    pmouseY = mouseY;

    //float64 x = 0, y = 0;
    glfwGetCursorPos(glfwWindow, &mouseX, &mouseY);

#ifdef _DEBUG
    //t2Log("Mouse:[x:%f, y:%f], butto:%d, state:%d\n", mouseX, mouseY, button, state);
#endif

    if(state == GLFW_PRESS)
        driver->triggerMouseEvent(mouseX, mouseY, pmouseX, pmouseY, button, TattyUI::T2_EVENT_MOUSE_PRESSED);
    else if(state == GLFW_RELEASE)
        driver->triggerMouseEvent(mouseX, mouseY, pmouseX, pmouseY, button, TattyUI::T2_EVENT_MOUSE_RELEASED);
}

static void cursorpos_cb(GLFWwindow* windowP_, double x, double y)
{
    TattyUI::t2EventController* driver = TattyUI::t2EventController::getInstance();

#ifdef _DEBUG
    //t2Log("Cursor:[x:%f, y:%f]\n", x, y);
#endif
    pmouseX = mouseX;
    pmouseY = mouseY;

    mouseX = x;
    mouseY = y;

    driver->triggerMouseEvent(x, y, pmouseX, pmouseY, TattyUI::T2_EVENT_NONE, TattyUI::T2_EVENT_MOUSE_MOVED);

}

static void keyboard_cb(GLFWwindow* windowP_, int key, int scancode, int action, int mods)
{
    TattyUI::t2EventController* driver = TattyUI::t2EventController::getInstance();

#ifdef _DEBUG
    //t2Log("Key:%d\n", key);
#endif

    // shift按下则转为大写字母
    if(key >= 65 && key <= 90 && (glfwGetKey(glfwWindow, T2_KEY_LEFT_SHIFT) || glfwGetKey(glfwWindow, T2_KEY_RIGHT_SHIFT)))
        key += 32;

    if(action == GLFW_PRESS || action == GLFW_REPEAT)
        driver->triggerKeyEvent(key, TattyUI::T2_EVENT_KEY_PRESSED);
    else if(action == GLFW_RELEASE)
        driver->triggerKeyEvent(key, TattyUI::T2_EVENT_KEY_RELEASED);
}

static void resize_cb(GLFWwindow* windowP_, int w, int h)
{
	//重新设置视区尺寸
	glViewport(0, 0, w, h);

	////重置坐标系统，使用投影变换复位
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//glOrtho(0.0f, w, h, 0, 1.0f, -1.0f);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

	// --!全局窗口大小
	t2SetWindowHeight(h);
	t2SetWindowWidth(w);
}

static void exit_cb(GLFWwindow* windowP_)
{
	T2_EXIT(0);
}

static void scroll_cb(GLFWwindow* windowP_, double x, double y)
{
    TattyUI::t2EventController* driver = TattyUI::t2EventController::getInstance();

    int32 button = T2_MOUSE_BUTTON_MIDDLE;

    driver->triggerMouseEvent(x, y, pmouseX, pmouseY, button, TattyUI::T2_EVENT_MOUSE_SCROLLED);
#ifdef _DEBUG
    //t2Log("%f,%f\n", x, y);
#endif

}

static void drop_cb(GLFWwindow* windowP_, const char* dropString)
{
}

static void error_cb(int errorCode, const char* errorDescription)
{
}
