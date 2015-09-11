#include <TattyUI/TattyUI.h>
#include <iostream>

using namespace TattyUI;

#define T2_GRAPHICS_TEST_1
//#define T2_GRAPHICS_TEST_2

int main(int argc, char* argv[])
{
    // TattyUI
    t2Window *window = new t2Window();
    window->setResizable(true);
    window->setMode(T2_WINDOW_WINDOWED);
    window->setup(960, 800);
    window->setTitle("TattyUI with nanovg");
    window->initCallBack();
    window->setVeticalSync(false);

    t2Renderer *renderer = t2Renderer::getInstance();
    renderer->loadFont("mono", "../resources/font/mono.ttf");
    renderer->setFont("mono");

    t2Image image;
    image.loadImage("../resources/image/2.jpeg");

    t2BoxGradient boxGradient;
    boxGradient.set(200, 200 + 6, 320, 320, 3, 20, t2Color(0, 0, 0, 90), t2Color(200, 200, 200, 0));

    while(1)
    {
        renderer->clear(238, 238, 238);

        renderer->begin();

#ifdef T2_GRAPHICS_TEST_1
        // rect
        renderer->setColor(20, 20, 200, 255);
        renderer->drawRect(10, 10, 200, 200);
        
        // roundrect
        renderer->setColor(20, 200, 200, 255);
        renderer->drawRoundRect(300, 300, 200, 200, 10);

        // ellipse
        renderer->setStrokeColor(40, 0, 0, 255);
        renderer->drawEllipse(200, 200, 40, 50, false);

        // circle
        renderer->setStrokeColor(0, 60, 0, 255);
        renderer->setStrokeWidth(10);
        renderer->drawCircle(200, 200, 100, false);

        // line
        renderer->setStrokeColor(0, 0, 0);
        renderer->setStrokeWidth(5);
        renderer->drawLine(100, 100, 400, 400);

        // text
        renderer->setTextColor(10, 10, 10);
        renderer->drawText(300, 100, 40, "Who's, Your Daddy?", 0);
        //renderer->drawText(300, 100, 40, "Who's, Your Daddy?", T2_ALIGN_LEFT | T2_ALIGN_TOP);
        renderer->drawText(300, 180, 40, "Who's, Your Daddy?", 0, T2_ALIGN_RIGHT | T2_ALIGN_MIDDLE);

        // image
        image.setStrokeWidth(5);
        image.drawInRect(200, 200, 640, 400, 0, 200, true);

        // gradient
        boxGradient.drawInRounedRect();

#else if T2_GRAPHICS_TEST_2

        boxGradient.drawInRounedRect();

        renderer->setColor(255, 255, 255, 255);
        renderer->drawRect(200, 200, 320, 320);
        //image.drawInRounedRect(200, 200, 640, 400, 25);
#endif


        renderer->end();

        window->swapBuffer();

        window->processEvents();
    }

    return 0;
}