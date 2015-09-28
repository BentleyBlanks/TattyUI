#include <TattyUI/TattyUI.h>
#include <TattyUI/test/fangcun/fcController.h>
#include <TattyUI/test/fangcun/fcRay.h>
#include <TattyUI/test/fangcun/fcCircle.h>
#include <Common/t3Timer.h>
using namespace TattyUI;

// common
t2Renderer *renderer;

t2Window *w;

t3Timer timer;

void initCommon()
{
    // TattyUI
    w = t2Window::getInstance();
    w->setWindowRadius(7);
    w->setTitleBarHeight(48);
    w->init("FangCun", "../resources/font/Roboto-Regular.ttf", 1280, 800, 200, 200);

    renderer = t2Renderer::getInstance();

    srand((unsigned) time(0));
}

void begin()
{
    renderer->clear(238, 238, 238);

    renderer->begin();
}

void end()
{
    w->draw();

    renderer->end();

    w->window->swapBuffer();

    w->window->processEvents();
}