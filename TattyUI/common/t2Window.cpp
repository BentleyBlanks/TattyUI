#include <TattyUI/common/t2Window.h>
#include <TattyUI/render/t2Gradient.h>

namespace TattyUI
{
    class t2Window::t2Button
    {
    public:
        void draw();

        void setClose(t2Image normal, t2Image hover, t2Image pressed);

        void setMaximize(t2Image normal, t2Image hover, t2Image pressed);

        void setMinimize(t2Image normal, t2Image hover, t2Image pressed);

        t2Image closeNormal, closeHover, closePressed;

        t2Image maximizeNormal, maximizeHover, maximizePressed;

        t2Image minimizeNormal, minimizeHover, minimizePressed;

        int status;
    };


    t2Point2i windowPosition;

    // t2Window
    t2Window* t2Window::getInstance()
    {
        static t2Window temp;
        return &temp;
    }

    t2Window::t2Window() :titleBarHeight(40), bDoubleClick(false), bDrag(false), windowRadius(20), bPressed(false)//, bReleased(false)
    {
        window = new t2WindowBase();

        titleBar = new t2LinearGradient();

        titleBarShadow = new t2BoxGradient();
    }

    void t2Window::init(string title, int width, int height, int positionX, int positionY)
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

        // 仿OSX
        //titleBar->set(0, 0, window->getWidth(), titleBarHeight, 0, 0, t2Color(200, 200, 200, 255), t2Color(246, 246, 246, 255));
        titleBar->set(0, 0, 0, titleBarHeight, window->getWidth(), titleBarHeight, t2Color(235, 235, 235, 255), t2Color(212, 212, 212, 255));
        titleBarShadow->set(0, 0, window->getWidth(), titleBarHeight, 0, 5, t2Color(0, 0, 0, 100), t2Color(0, 0, 0, 0));
    }

    void t2Window::draw()
    {
        titleBarShadow->drawInRounedRect();
        titleBar->drawInRect();
    }

    void t2Window::setTitleBar(int height)
    {
        titleBarHeight = height;
    }

    int t2Window::getTitleBar()
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

    }

    void t2Window::setMaximize(t2Image normal, t2Image hover, t2Image pressed)
    {

    }

    void t2Window::setMinimize(t2Image normal, t2Image hover, t2Image pressed)
    {

    }

    bool t2Window::inTitleBar(int x, int y)
    {
        if(y <= titleBarHeight && y >= 0 && x >= 0 && x <= window->getWidth())
            return true;
        else
            return false;
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
    }

    void t2Window::onMouseReleased(int x, int y, int px, int py, int button)
    {
        bPressed = false;
    }

    void t2Window::onMouseMoved(int x, int y, int px, int py)
    {
        if(inTitleBar(x, y) && bPressed)
            window->setPosition(t2GetMouseAbsoluteX() - tx, t2GetMouseAbsoluteY() - ty);

    }
}