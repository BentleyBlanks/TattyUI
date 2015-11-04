#ifndef T2_WINDOWBASE_H
#define T2_WINDOWBASE_H

#include <TattyUI/common/t2Vector2.h>

struct GLFWwindow;

namespace TattyUI
{
	class t2WindowBase
	{
	public:
		t2WindowBase();

		void setup(int width, int height);

		// getter/setter
		// --!get
		t2Point2i getSize();

		t2Point2i getPosition(); 

		int getHeight();

		int getWidth();

        void setRadius(int raidus);

		// 垂直同步
		bool isVerticalSync();

		int getMode();

		t2Point2i getScreenSize();
		// --!set
		// 窗口自身属性设置
		void setPosition(int x, int y);

		void setPosition(t2Point2i position);

		void setSize(int width, int height);

		void setSize(const t2Point2i size);

		void setResizable(bool resizable);

		void setHeight(int height);

		void setWidth(int width);

		void setMode(int mode);

		void setTitle(std::string title);

        std::string getTitle();

		void setIcon();

        // 最小化 最大化操作
        void maximize();

        void minimize();

		// 窗口相关属性
		void setVeticalSync(bool verticalSync);

		void hideCursor(bool hide);

		void swapBuffer();

		void processEvents();

		// 挂钩所有回调函数
		void initCallBack();

		void exit();

	protected:

		// --!不使用int是防止特殊需求
		int width, height;
		// 使用引用/指针防止报错
		t2Vector2i size;
		// 绝对位置
		t2Vector2i position;
		// 窗口模式
		// --!不清楚为何int不能转换为tkWindowMode
		int mode;
		// 垂直同步
		bool verticalSync;
		// 可否变换窗口大小
		bool resizable;
		// 窗口标题
		std::string title;

        int radius;

	private:
		// 投影矩阵等初始化
		void set2d(float width = 0, float height = 0);
		// 内部使用函数
		void setFullScreen();
		// 获得当前焦点显示器的序号
		int getCurrentMonitor();
        // 初始化glew
        bool initGlew();
	};
}

#ifdef T2_PLATFORM_WINDOWS
HWND getHwnd();
#endif


GLFWwindow* getGLFWWindow();

// mouse
void t2GetMousePos(double *x, double *y);

TattyUI::t2Point2i t2GetMouseAbsolutePos();

void t2UpdateAbsoluteMousePos();

int t2GetMouseAbsoluteX();

int t2GetMouseAbsoluteY();

int t2GetPreviousMouseAbsoluteX();

int t2GetPreviousMouseAbsoluteY();

double t2GetMouseX();

double t2GetMouseY();

#endif
