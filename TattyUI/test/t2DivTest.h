#include <TattyUI/TattyUI.h>
#include <iostream>

using namespace TattyUI;

int main(int argc, char* argv[])
{
    // TattyUI
    t2Window *window = new t2Window();
    window->setPosition(200, 200);
    window->setResizable(true);
    window->setMode(T2_WINDOW_WINDOWED);
    window->setup(960, 640);
    window->setTitle("TattyUI");
    window->initCallBack();
    window->setVeticalSync(false);

    t2Renderer *renderer = t2Renderer::getInstance();
    renderer->loadFont("mono", "../resources/font/mono.ttf");
    renderer->setFont("mono");

    renderer->loadFont("regular", "../resources/font/Roboto-Regular.ttf");
    renderer->setFont("regular");

    t2Div div(400, 267, "mono", "../resources/font/mono.ttf");
    div.normal.x = window->getWidth() / 2 - 200;
    div.normal.y = 100;

    div.normal.backgroundColor.set(250, 250, 250);
    div.normal.boxShadowColor.set(0, 0, 0, 100);
    div.normal.boxShadowBlur = 10;
    div.normal.vBoxShadow = 4;
    div.normal.borderRadius = 5;

    div.normal.backgroundImage.loadImage("../resources/image/2.jpeg");

    div.normal.textColor.set(200, 200, 200, 255);
    div.normal.fontName = "mono";
    div.normal.fontSize = 40;
    div.normal.textAlign = T2_TEXT_RIGHT | T2_TEXT_BOTTOM;
    div.normal.text = "Who's Your Daddy";

    div.active = div.normal;
    //div.active.textColor.set(20, 20, 20, 255);

    div.hover = div.normal;
    //div.hover.textColor.set(200, 20, 20, 255);

    div.init();

    t2Div button(150, 40, "regular", "../resources/font/Roboto-Regular.ttf");
    button.normal.x = window->getWidth() / 2 - 75 - 270;
    button.normal.y = 470;

    button.normal.backgroundColor.set(28, 131, 193);
    button.normal.boxShadowColor.set(0, 0, 0, 100);
    button.normal.boxShadowBlur = 4;
    button.normal.vBoxShadow = 2;
    button.normal.borderRadius = 5;

    button.normal.textColor.set(255, 255, 255, 255);
    button.normal.fontName = "regular";
    button.normal.fontSize = 20;
    button.normal.textAlign = T2_TEXT_CENTER | T2_TEXT_MIDDLE;
    button.normal.text = "I'm";

    button.active = button.normal;
    button.active.backgroundColor.set(46, 104, 152);

    button.hover = button.normal;
    button.hover.backgroundColor.set(95, 156, 207);

    button.init();

    t2Div button1(150, 40, "regular", "../resources/font/Roboto-Regular.ttf");
    button1.normal.x = window->getWidth() / 2 - 75;
    button1.normal.y = 470;

    button1.normal.backgroundColor.set(217, 92, 92);
    button1.normal.boxShadowColor.set(0, 0, 0, 100);
    button1.normal.boxShadowBlur = 4;
    button1.normal.vBoxShadow = 2;
    button1.normal.borderRadius = 5;

    button1.normal.textColor.set(255, 255, 255, 255);
    button1.normal.fontName = "regular";
    button1.normal.fontSize = 20;
    button1.normal.textAlign = T2_TEXT_CENTER | T2_TEXT_MIDDLE;
    button1.normal.text = "Your";

    button1.active = button1.normal;
    button1.active.backgroundColor.set(209, 61, 61);

    button1.hover = button1.normal;
    button1.hover.backgroundColor.set(233, 121, 121);

    button1.init();

    t2Div button2(150, 40, "regular", "../resources/font/Roboto-Regular.ttf");
    button2.normal.x = window->getWidth() / 2 - 75 + 270;
    button2.normal.y = 470;

    button2.normal.backgroundColor.set(0, 181, 173);
    button2.normal.boxShadowColor.set(0, 0, 0, 100);
    button2.normal.boxShadowBlur = 4;
    button2.normal.vBoxShadow = 2;
    button2.normal.borderRadius = 5;

    button2.normal.textColor.set(255, 255, 255, 255);
    button2.normal.fontName = "regular";
    button2.normal.fontSize = 20;
    button2.normal.textAlign = T2_TEXT_CENTER | T2_TEXT_MIDDLE;
    button2.normal.text = "Father";

    button2.active = button2.normal;
    button2.active.backgroundColor.set(0, 181, 173);

    button2.hover = button2.normal;
    button2.hover.backgroundColor.set(0, 210, 200);

    button2.init();

    t2DivController *divController = t2DivController::getInstance();
    divController->addDiv("Who's Your Daddy", &div);
    divController->addDiv("I'm", &button);
    divController->addDiv("Your", &button1);
    divController->addDiv("Father", &button2);

    div.mouseMovedIn = [&div](int x, int y, int px, int py)
    {
        t2Log("Mouse Moved In\n");
    };

    div.mouseMovedOut = [&div](int x, int y, int px, int py)
    {
        t2Log("Mouse Moved Out\n");
    };

    div.mousePressed = [&div](int x, int y, int px, int py, int button)
    {
        t2Log("Mouse Pressed\n");
    };

    div.mouseReleased = [&div](int x, int y, int px, int py, int button)
    {
        t2Log("Mouse Release\n");
    };

    button.mouseReleased = [&div](int x, int y, int px, int py, int button)
    {
        t2Log("I'm\n");
    };

    button1.mouseReleased = [&div](int x, int y, int px, int py, int button)
    {
        t2Log("Your\n");
    };

    button2.mouseReleased = [&div](int x, int y, int px, int py, int button)
    {
        t2Log("Father\n");
    };

    while(1)
    {
        renderer->clear(238, 238, 238);

        renderer->begin();

        divController->draw();

        renderer->end();

        window->swapBuffer();

        window->processEvents();
    }

    return 0;
}