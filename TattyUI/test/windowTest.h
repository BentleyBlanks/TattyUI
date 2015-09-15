#include <TattyUI/TattyUI.h>
using namespace TattyUI;

int main()
{
    t2Window *w = t2Window::getInstance();
    w->setWindowRadius(7);
    w->setTitleBar(53);
    w->init("TattyUI", 960, 640, 200, 200);

    t2Renderer *renderer = t2Renderer::getInstance();

    while(1)
    {
        renderer->clear(238, 238, 238);

        renderer->begin();

        w->draw();

        renderer->end();

        w->window->swapBuffer();

        w->window->processEvents();
    }

    return 0;
}