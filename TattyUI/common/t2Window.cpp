#include <TattyUI/common/t2Window.h>
#include <TattyUI/render/t2Gradient.h>
#include <TattyUI/div/t2Div.h>
#include <TattyUI/render/t2Renderer.h>

namespace TattyUI
{
    enum t2WindowStatus
    {
        T2_WINDOW_MINIMIZE,
        T2_WINDOW_MAXIMIZE,
        T2_WINDOW_CLOSE,

        T2_WINDOW_NONE  // 空消息
    };

    class t2Window::t2Button
    {
    public:
        t2Button(t2WindowBase* window);

        void draw();

        void init();

        void setClose(t2Image normal, t2Image hover, t2Image pressed);

        void setMaximize(t2Image normal, t2Image hover, t2Image pressed);

        void setMinimize(t2Image normal, t2Image hover, t2Image pressed);

        bool inClose(int x, int y);

        bool inMaximize(int x, int y);

        bool inMinimize(int x, int y);

        // 处理拖动窗口 双击窗口等事件
        virtual void onMousePressed(int x, int y, int px, int py, int button);

        virtual void onMouseReleased(int x, int y, int px, int py, int button);

        virtual void onMouseMoved(int x, int y, int px, int py);

        t2Image closeNormal, closeHover, closePressed;

        t2Image maximizeNormal, maximizeHover, maximizePressed;

        t2Image minimizeNormal, minimizeHover, minimizePressed;

        t2Point2i closePos, maximizePos, minimizePos;

        int closeStatus, maximizeStatus, minimizeStatus;

        // 拷贝
        t2WindowBase* window;
    };

    t2Window::t2Button::t2Button(t2WindowBase* window) :closeStatus(T2_NORMAL), maximizeStatus(T2_NORMAL), minimizeStatus(T2_NORMAL), window(window)
    {
        closePos.set(14, 14);

        maximizePos.set(34, 14);

        minimizePos.set(54, 14);
    }

    void t2Window::t2Button::init()
    {
        closeNormal.loadImage("../resources/image/closeNormal.png");
        closeHover.loadImage("../resources/image/closeHover.png");
        closePressed.loadImage("../resources/image/closePressed.png");

        maximizeNormal.loadImage("../resources/image/maximizeNormal.png");
        maximizeHover.loadImage("../resources/image/maximizeHover.png");
        maximizePressed.loadImage("../resources/image/maximizePressed.png");

        minimizeNormal.loadImage("../resources/image/minimizeNormal.png");
        minimizeHover.loadImage("../resources/image/minimizeHover.png");
        minimizePressed.loadImage("../resources/image/minimizePressed.png");
    }

    void t2Window::t2Button::draw()
    {
        //// close
        //switch(closeStatus)
        //{
        //case T2_NORMAL:
        //    closeNormal.drawInRect(closeNormal.getWidth(), closeNormal.getHeight(), closeNormal.getWidth(), closeNormal.getHeight());
        //    break;
        //
        //case T2_HOVER:
        //    closeHover.drawInRect(closeHover.getWidth(), closeHover.getHeight(), closeHover.getWidth(), closeHover.getHeight());
        //    break;
        //
        //case T2_ACTIVE:
        //    closePressed.drawInRect(closePressed.getWidth(), closePressed.getHeight(), closePressed.getWidth(), closePressed.getHeight());
        //    break;
        //}
        //
        //// maximize
        //switch(maximizeStatus)
        //{
        //case T2_NORMAL:
        //    maximizeNormal.drawInRect(maximizeNormal.getWidth(), maximizeNormal.getHeight(), maximizeNormal.getWidth(), maximizeNormal.getHeight());
        //    break;
        //
        //case T2_HOVER:
        //    maximizeHover.drawInRect(maximizeHover.getWidth(), maximizeHover.getHeight(), maximizeHover.getWidth(), maximizeHover.getHeight());
        //    break;
        //
        //case T2_ACTIVE:
        //    maximizePressed.drawInRect(maximizePressed.getWidth(), maximizePressed.getHeight(), maximizePressed.getWidth(), maximizePressed.getHeight());
        //    break;
        //}
        //
        ////minimize
        //switch(minimizeStatus)
        //{
        //case T2_NORMAL:
        //    minimizeNormal.drawInRect(minimizeNormal.getWidth(), minimizeNormal.getHeight(), minimizeNormal.getWidth(), minimizeNormal.getHeight());
        //    break;
        //
        //case T2_HOVER:
        //    minimizeHover.drawInRect(minimizeHover.getWidth(), minimizeHover.getHeight(), minimizeHover.getWidth(), minimizeHover.getHeight());
        //    break;
        //
        //case T2_ACTIVE:
        //    minimizePressed.drawInRect(minimizePressed.getWidth(), minimizePressed.getHeight(), minimizePressed.getWidth(), minimizePressed.getHeight());
        //    break;
        //}

        

        // close
        switch(closeStatus)
        {
        case T2_NORMAL:
            if(closeNormal.isLoaded())
                closeNormal.drawInRect(closePos.x, closePos.y, closeNormal.getWidth(), closeNormal.getHeight());
            else
                t2Log("未能加载icon: closeNormal\n");
            break;

        case T2_HOVER:
            if(closeHover.isLoaded())
                closeHover.drawInRect(closePos.x, closePos.y, closeHover.getWidth(), closeHover.getHeight());
            else
                t2Log("未能加载icon: closeHover\n");
            break;

        case T2_ACTIVE:
            if(closePressed.isLoaded())
                closePressed.drawInRect(closePos.x, closePos.y, closePressed.getWidth(), closePressed.getHeight());
            else
                t2Log("未能加载icon: closePressed\n");
            break;
        }

        // maximize
        switch(maximizeStatus)
        {
        case T2_NORMAL:
            if(maximizeNormal.isLoaded())
                maximizeNormal.drawInRect(maximizePos.x, maximizePos.y, maximizeNormal.getWidth(), maximizeNormal.getHeight());
            else
                t2Log("未能加载icon: maximizeNormal\n");
            break;

        case T2_HOVER:
            if(maximizeHover.isLoaded())
                maximizeHover.drawInRect(maximizePos.x, maximizePos.y, maximizeHover.getWidth(), maximizeHover.getHeight());
            else
                t2Log("未能加载icon: maximizeHover\n");
            break;

        case T2_ACTIVE:
            if(maximizePressed.isLoaded())
                maximizePressed.drawInRect(maximizePos.x, maximizePos.y, maximizePressed.getWidth(), maximizePressed.getHeight());
            else
                t2Log("未能加载icon: maximizePressed\n");
            break;
        }

        //minimize
        switch(minimizeStatus)
        {
        case T2_NORMAL:
            if(minimizeNormal.isLoaded())
                minimizeNormal.drawInRect(minimizePos.x, minimizePos.y, minimizeNormal.getWidth(), minimizeNormal.getHeight());
            else
                t2Log("未能加载icon: minimizeNormal\n");
            break;

        case T2_HOVER:
            if(minimizeNormal.isLoaded())
                minimizeHover.drawInRect(minimizePos.x, minimizePos.y, minimizeHover.getWidth(), minimizeHover.getHeight());
            else
                t2Log("未能加载icon: minimizeHover\n");
            break;

        case T2_ACTIVE:
            if(minimizePressed.isLoaded())
                minimizePressed.drawInRect(minimizePos.x, minimizePos.y, minimizePressed.getWidth(), minimizePressed.getHeight());
            else
                t2Log("未能加载icon: minimizePressed\n");
            break;
        }
    }

    void t2Window::t2Button::setClose(t2Image normal, t2Image hover, t2Image pressed)
    {
        closeNormal = normal;
        closeHover = hover;
        closePressed = pressed;
    }

    void t2Window::t2Button::setMaximize(t2Image normal, t2Image hover, t2Image pressed)
    {
        maximizeNormal = normal;
        maximizeHover = hover;
        maximizePressed = pressed;
    }

    void t2Window::t2Button::setMinimize(t2Image normal, t2Image hover, t2Image pressed)
    {
        minimizeNormal = normal;
        minimizeHover = hover;
        minimizePressed = pressed;
    }

    void t2Window::t2Button::onMousePressed(int x, int y, int px, int py, int button)
    {
        if(inClose(x, y))
        {
            closeStatus = T2_ACTIVE;
        }
        else if(inMaximize(x, y))
        {
            maximizeStatus = T2_ACTIVE;
        }
        else if(inMinimize(x, y))
        {
            minimizeStatus = T2_ACTIVE;
        }
    }

    void t2Window::t2Button::onMouseReleased(int x, int y, int px, int py, int button)
    {
        if(inClose(x, y))
        {
            closeStatus = T2_NORMAL;

            window->exit();
        }
        else if(inMaximize(x, y))
        {
            maximizeStatus = T2_NORMAL;

            window->maximize();

            t2Window *w = t2Window::getInstance();
            w->resized();
        }
        else if(inMinimize(x, y))
        {
            minimizeStatus = T2_NORMAL;

            window->minimize();
        }
    }

    void t2Window::t2Button::onMouseMoved(int x, int y, int px, int py)
    {
        // move in
        if(inClose(x, y) && !inClose(px, py))
            closeStatus = T2_HOVER;
        // move out
        else if(!inClose(x, y) && inClose(px, py))
            closeStatus = T2_NORMAL;

        // move in
        if(inMaximize(x, y) && !inMaximize(px, py))
            maximizeStatus = T2_HOVER;
        // move out
        else if(!inMaximize(x, y) && inMaximize(px, py))
            maximizeStatus = T2_NORMAL;

        // move in
        if(inMinimize(x, y) && !inMinimize(px, py))
            minimizeStatus = T2_HOVER;
        // move out
        else if(!inMinimize(x, y) && inMinimize(px, py))
            minimizeStatus = T2_NORMAL; 
    }

    bool t2Window::t2Button::inClose(int x, int y)
    {
        if(x >= closePos.x && x <= closePos.x + closeNormal.getWidth() &&
           y >= closePos.y && y <= closePos.y + closeNormal.getHeight())
            return true;
        else
            return false;
    }

    bool t2Window::t2Button::inMaximize(int x, int y)
    {
        if(x >= maximizePos.x && x <= maximizePos.x + maximizeNormal.getWidth() &&
           y >= maximizePos.y && y <= maximizePos.y + maximizeNormal.getHeight())
           return true;
        else
            return false;
    }

    bool t2Window::t2Button::inMinimize(int x, int y)
    {
        if(x >= minimizePos.x && x <= minimizePos.x + minimizeNormal.getWidth() &&
           y >= minimizePos.y && y <= minimizePos.y + minimizeNormal.getHeight())
           return true;
        else
            return false;
    }

    // t2Window
    t2Window* t2Window::getInstance()
    {
        static t2Window temp;
        return &temp;
    }

    t2Window::t2Window() :titleBarHeight(48), bDoubleClick(false), bDrag(false), windowRadius(7), bPressed(false)//, bReleased(false)
    {
        window = new t2WindowBase();

        titleBar = new t2LinearGradient();

        titleBarShadow = new t2BoxGradient();
    }

    void t2Window::init(string title, string fontFamily, int width, int height, int positionX, int positionY)
    {
        // 未来开放给Lua
        window->setRadius(windowRadius);
        window->setResizable(false);
        window->setMode(T2_WINDOW_NOTITLE);
        window->setup(width, height);
        window->setPosition(positionX, positionY);
        window->setTitle(title);
        window->initCallBack();
        window->setVeticalSync(false);

        renderer = t2Renderer::getInstance();
        titileFontFamily = fontFamily;
        renderer->loadFont(fontFamily.c_str(), fontFamily.c_str());

        // 仿OSX
        titleBar->set(0, 0, 0, titleBarHeight, window->getWidth(), titleBarHeight, t2Color(33, 33, 33, 255), t2Color(8, 8, 8, 255));
        titleBarShadow->set(0, 0, window->getWidth(), titleBarHeight, 0, 5, t2Color(0, 0, 0, 100), t2Color(0, 0, 0, 0));

        buttons = new t2Button(window);
        buttons->init();
    }

    void t2Window::draw()
    {
        titleBarShadow->drawInRounedRect();

        titleBar->drawInRect();

        renderer->setStrokeColor(0, 0, 0, 255);
        renderer->setStrokeWidth(0.5);
        //renderer->drawLine(0, titleBarHeight, window->getWidth(), titleBarHeight);
        renderer->drawRect(0, 0, window->getWidth(), titleBarHeight, false);
        //renderer->drawRoundRect(0, 0, window->getWidth(), titleBarHeight, windowRadius, false);

        buttons->draw();

        renderer->setFont(titileFontFamily.c_str());
        renderer->setTextColor(212, 212, 212);
        renderer->drawText(window->getWidth() / 2 , titleBarHeight / 2, 18, window->getTitle(), 0, T2_TEXT_CENTER | T2_TEXT_MIDDLE);
    }

    void t2Window::setTitleBarHeight(int height)
    {
        titleBarHeight = height;
    }

    int t2Window::getTitleBarHeight()
    {
        return titleBarHeight;
    }

    void t2Window::setDrag(bool drag)
    {
        bDrag = drag;
    }

    void t2Window::setDoubleClick(bool doubleClick)
    {
        bDoubleClick = doubleClick;
    }

    void t2Window::setClose(t2Image normal, t2Image hover, t2Image pressed)
    {
        buttons->setClose(normal, hover, pressed);
    }

    void t2Window::setMaximize(t2Image normal, t2Image hover, t2Image pressed)
    {
        buttons->setMaximize(normal, hover, pressed);
    }

    void t2Window::setMinimize(t2Image normal, t2Image hover, t2Image pressed)
    {
        buttons->setMinimize(normal, hover, pressed);
    }

    bool t2Window::inTitleBar(int x, int y)
    {
        if(y <= titleBarHeight && y >= 0 && x >= 0 && x <= window->getWidth())
            return true;
        else
            return false;
    }

    void t2Window::resized()
    {
        // 重设标题栏
        titleBar->set(0, 0, 0, titleBarHeight, window->getWidth(), titleBarHeight, t2Color(33, 33, 33, 255), t2Color(8, 8, 8, 255));
        titleBarShadow->set(0, 0, window->getWidth(), titleBarHeight, 0, 5, t2Color(0, 0, 0, 100), t2Color(0, 0, 0, 0));
    }

    void t2Window::setWindowRadius(int raidus)
    {
        windowRadius = raidus;
    }

    static int tx, ty;
    void t2Window::onMousePressed(int x, int y, int px, int py, int button)
    {
        if(!inTitleBar(x, y))
            return;

        tx = x - 8;
        ty = y - 30;
        bPressed = true;

        buttons->onMousePressed(x, y, px, py, button);
    }

    void t2Window::onMouseReleased(int x, int y, int px, int py, int button)
    {
        bPressed = false;

        // --!可更正为windowResized
        buttons->onMouseReleased(x, y, px, py, button);
    }

    void t2Window::onMouseMoved(int x, int y, int px, int py)
    {
        if(inTitleBar(x, y))
        {
            if(bPressed)
                window->setPosition(t2GetMouseAbsoluteX() - tx, t2GetMouseAbsoluteY() - ty);

            buttons->onMouseMoved(x, y, px, py);
        }
    }
}