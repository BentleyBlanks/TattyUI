#include <TattyUI/TattyUI.h>
using namespace TattyUI;

int main()
{
    t2Window *w = t2Window::getInstance();
    w->setWindowRadius(7);
    w->setTitleBarHeight(48);
    w->init("TattyUI", "../resources/font/Roboto-Regular.ttf", 1280, 800, 200, 200);

    t2Div root, div1, div2, div3;

    root.className = "root";
    div1.className = "div1";
    div2.className = "div2";
    div3.className = "div3";

    root.normal.text = "Root";
    div1.normal.text = "Div1";
    div2.normal.text = "Div2";
    div3.normal.text = "Div3";

    root.hover.text = "Root";
    div1.hover.text = "Div1";
    div2.hover.text = "Div2";
    div3.hover.text = "Div3";

    root.active.text = "Root";
    div1.active.text = "Div1";
    div2.active.text = "Div2";
    div3.active.text = "Div3";

    div1.parent = &root;
    div2.parent = &root;
    div3.parent = &root;

    div1.next = &div2;
    div2.next = &div3;

    root.child = &div1;

    t2Renderer *renderer = t2Renderer::getInstance();

    t2DivController *divController = t2DivController::getInstance();
    divController->addDiv("div2", &div2);
    divController->addDiv("div1", &div1);
    divController->addDiv("root", &root);
    divController->addDiv("div3", &div3);

    divController->setRoot("root");

    // --!htmlController一步完成
    t2CSSController *cssCon = t2CSSController::getInstance();
    vector<string> files;
    files.push_back("../bin/script/css/test2.css");
    cssCon->loadCSS(files);

    divController->init();

    while(1)
    {
        renderer->clear(238, 238, 238);

        renderer->begin();

        divController->draw();

        w->draw();

        renderer->end();

        w->window->swapBuffer();

        w->window->processEvents();
    }

    return 0;
}