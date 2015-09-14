#ifndef T2_DIV_H
#define T2_DIV_H

#include <TattyUI/div/t2Style.h>
#include <functional>

namespace TattyUI
{
    enum t2DivStatus
    {
        T2_NORAML,
        T2_ACTIVE,
        T2_HOVER
    };

    class t2Div
    {
    public:
        t2Div(int width, int height, string fontName, string fontPath);

        // --!一定要在css内容都已经完成赋值后才可调用
        // 初始化具体div属性默认内容，包括内外边距阴影初始化
        void init();

        //void update();

        void draw();

        void setStatus(int status);

        int getStatus();

        // 获取当前状态的样式表
        t2Style& getCSS();

        t2Style normal, active, hover;

        // 父节点 / 兄弟节点 / 第一个孩子节点
        t2Div* parent, *next, *child;

        // --!测试使用
        // 是否渲染padding margin包围盒
        bool bDrawPaddingAABB, bDrawMarginAABB;

        // 回调 所有callback都指定为这此
         std::function<void(int x, int y, int px, int py, int button)> mousePressed;

         std::function<void(int x, int y, int px, int py, int button)> mouseReleased;

         std::function<void(int x, int y, int px, int py)> mouseMoved;

         // 鼠标移入移出回调
         std::function<void(int x, int y, int px, int py)> mouseMovedIn;

         std::function<void(int x, int y, int px, int py)> mouseMovedOut;

         std::function<void(int x, int y, int px, int py)> mouseScrolled;

         std::function<void(int key)> keyPressed;

         std::function<void(int key)> keyReleased;
    private:
        // 根据兄弟结点 父节点位置更新自身实际渲染位置
        void updateContent();

        virtual void onMousePressed(int x, int y, int px, int py, int button);

        virtual void onMouseReleased(int x, int y, int px, int py, int button);

        virtual void onMouseMoved(int x, int y, int px, int py);

        virtual void onMouseScrolled(int x, int y, int px, int py);

        virtual void onKeyPressed(int key);

        virtual void onKeyReleased(int key);

        friend class t2DivController;

        int status;

    };
}

#endif