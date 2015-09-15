#ifndef T2_WINDOW_H
#define T2_WINDOW_H

#include <TattyUI/render/t2Image.h>
#include <TattyUI/common/t2WindowBase.h>

namespace TattyUI
{
    class t2LinearGradient;
    class t2BoxGradient;
    //class t2WindowBase;
    // 设置成单例不能支持多窗口 个人感觉没关系
    class t2Window
    {
    public:
        static t2Window* getInstance();

        void init(string title, int width, int height, int positionX = 0, int positionY = 0);

        void draw();

        void setTitleBar(int height);

        int getTitleBar();

        void setDrag(bool drag);

        void setDoubleClick(bool doubleClick);

        void setClose(t2Image normal, t2Image hover, t2Image pressed);

        void setMaximize(t2Image normal, t2Image hover, t2Image pressed);

        void setMinimize(t2Image normal, t2Image hover, t2Image pressed);

        void setWindowRadius(int raidus);

        // 给定点是否在标题栏中
        bool inTitleBar(int x, int y);

        // 实际窗口
        t2WindowBase* window;

    protected:
        // 不可删除 不可复制 不可自己创建实例
        t2Window();
        t2Window(const t2Window&) {}
        ~t2Window() {}
        t2Window& operator=(const t2Window& event) const {}

        friend class t2EventController;

        // 处理拖动窗口 双击窗口等事件
        virtual void onMousePressed(int x, int y, int px, int py, int button);

        virtual void onMouseReleased(int x, int y, int px, int py, int button);

        virtual void onMouseMoved(int x, int y, int px, int py);

        // 最小化 最大化 关闭按钮
        class t2Button;
        t2Button *close, *maximize, *minimize;

        // 标题栏高度
        int titleBarHeight;

        // 窗口圆角
        int windowRadius;

        bool bDoubleClick, bDrag;
        bool bPressed;

        // 标题栏
        t2LinearGradient *titleBar;
        t2BoxGradient *titleBarShadow;
    };
}

#endif