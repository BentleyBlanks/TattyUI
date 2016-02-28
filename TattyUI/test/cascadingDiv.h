#include <TattyUI/TattyUI.h>
#include <Common/t3Timer.h>

using namespace TattyUI;

int main()
{
    // TattyUI
    t2WindowBase *window = new t2WindowBase();
    window->setResizable(true);
    window->setMode(T2_WINDOW_WINDOWED);
    window->setup(960, 960);
    window->setPosition(50, 50);
    window->setTitle("TattyUI");
    window->initCallBack();
    window->setVeticalSync(false);

    t2Div root(200, 100, "mono", "../resources/font/Roboto-Regular.ttf"),
        div1(210, 100, "mono", "../resources/font/Roboto-Regular.ttf"),
        div2(210, 100, "mono", "../resources/font/Roboto-Regular.ttf"),
        div3(240, 100, "mono", "../resources/font/Roboto-Regular.ttf"),
        div4(240, 100, "mono", "../resources/font/Roboto-Regular.ttf"),
        div5(240, 100, "mono", "../resources/font/Roboto-Regular.ttf"),
        div6(240, 100, "mono", "../resources/font/Roboto-Regular.ttf"),
        div7(240, 100, "mono", "../resources/font/Roboto-Regular.ttf"),
        div8(450, 100, "mono", "../resources/font/Roboto-Regular.ttf"),
        div9(350, 100, "mono", "../resources/font/Roboto-Regular.ttf");

    root.normal.width = 800;
    root.normal.height = 800;
    root.normal.backgroundColor.set(100, 50, 50);
    root.normal.paddingLeft = 30;
    root.normal.paddingTop = 30;
    root.normal.paddingBottom = 30;
    root.normal.paddingRight = 30;
    root.normal.marginLeft = 30;
    root.normal.marginBottom = 30;
    root.normal.marginRight = 30;
    root.normal.marginTop = 30;
    root.normal.text = "root";
    root.normal.fontSize = 25;
    root.normal.textAlign = T2_TEXT_LEFT | T2_TEXT_TOP;
    root.active = root.normal;
    root.hover = root.normal;
    root.bDrawMarginAABB = true;
    root.bDrawPaddingAABB = true;

    div1.normal.backgroundColor.set(200, 100, 50);
    div1.normal.paddingLeft = 30;
    div1.normal.paddingTop = 40;
    div1.normal.text = "div1";
    div1.normal.fontSize = 25;
    div1.active = div1.normal;
    div1.hover = div1.normal;
    div1.bDrawMarginAABB = true;
    div1.bDrawPaddingAABB = true;

    div2.normal.backgroundColor.set(200, 50, 200);
    div2.normal.paddingLeft = 30;
    div2.normal.paddingTop = 30;
    div2.normal.paddingBottom = 30;
    div2.normal.paddingRight = 30;
    div2.normal.marginLeft = 30;
    div2.normal.marginBottom = 30;
    div2.normal.marginRight = 30;
    div2.normal.marginTop = 30;
    div2.normal.text = "div2";
    div2.normal.fontSize = 25;
    div2.active = div2.normal;
    div2.hover = div2.normal;
    div2.bDrawMarginAABB = true;
    div2.bDrawPaddingAABB = true;

    div3.normal.backgroundColor.set(200, 200, 200);
    div2.normal.marginLeft = 30;
    div3.normal.paddingLeft = 30;
    div3.normal.paddingTop = 40;
    div3.normal.text = "div3";
    div3.normal.fontSize = 25;
    div3.active = div3.normal;
    div3.hover = div3.normal;
    div3.bDrawMarginAABB = true;
    div3.bDrawPaddingAABB = true;

    div4.normal.backgroundColor.set(50, 200, 200);
    div4.normal.paddingLeft = 30;
    div4.normal.paddingTop = 30;
    div4.normal.paddingBottom = 30;
    div4.normal.paddingRight = 30;
    div4.normal.marginLeft = 30;
    div4.normal.marginBottom = 30;
    div4.normal.marginRight = 30;
    div4.normal.marginTop = 30;
    div4.normal.text = "div4";
    div4.normal.fontSize = 25;
    div4.active = div4.normal;
    div4.hover = div4.normal;
    div4.bDrawMarginAABB = true;
    div4.bDrawPaddingAABB = true;

    div5.normal.backgroundColor.set(50, 200, 200);
    div5.normal.paddingLeft = 30;
    div5.normal.paddingTop = 30;
    div5.normal.paddingBottom = 30;
    div5.normal.paddingRight = 30;
    div5.normal.marginLeft = 30;
    div5.normal.marginBottom = 30;
    div5.normal.marginRight = 30;
    div5.normal.marginTop = 30;
    div5.normal.text = "div5";
    div5.normal.fontSize = 25;
    div5.active = div5.normal;
    div5.hover = div5.normal;
    div5.bDrawMarginAABB = true;
    div5.bDrawPaddingAABB = true;

    div6.normal.backgroundColor.set(50, 200, 200);
    div6.normal.paddingLeft = 30;
    div6.normal.paddingTop = 30;
    div6.normal.paddingBottom = 30;
    div6.normal.paddingRight = 30;
    div6.normal.marginLeft = 30;
    div6.normal.marginBottom = 30;
    div6.normal.marginRight = 30;
    div6.normal.marginTop = 30;
    div6.normal.text = "div6";
    div6.normal.fontSize = 25;
    div6.active = div6.normal;
    div6.hover = div6.normal;
    div6.bDrawMarginAABB = true;
    div6.bDrawPaddingAABB = true;

    div7.normal.backgroundColor.set(50, 200, 200);
    div7.normal.paddingLeft = 30;
    div7.normal.paddingTop = 30;
    div7.normal.paddingBottom = 30;
    div7.normal.paddingRight = 30;
    div7.normal.marginLeft = 30;
    div7.normal.marginBottom = 30;
    div7.normal.marginRight = 30;
    div7.normal.marginTop = 30;
    div7.normal.text = "div7";
    div7.normal.fontSize = 25;
    div7.active = div7.normal;
    div7.hover = div7.normal;
    div7.bDrawMarginAABB = true;
    div7.bDrawPaddingAABB = true;

    div8.normal.backgroundColor.set(200, 100, 50);
    div8.normal.paddingLeft = 30;
    div8.normal.paddingTop = 40;
    div8.normal.text = "div8";
    div8.normal.fontSize = 25;
    div8.active = div8.normal;
    div8.hover = div8.normal;
    div8.bDrawMarginAABB = true;
    div8.bDrawPaddingAABB = true;

    div9.normal.backgroundColor.set(200, 100, 50);
    div9.normal.paddingLeft = 30;
    div9.normal.paddingTop = 40;
    div9.normal.text = "div9";
    div9.normal.fontSize = 25;
    div9.active = div9.normal;
    div9.hover = div9.normal;
    div9.bDrawMarginAABB = true;
    div9.bDrawPaddingAABB = true;

    // 层级关系
    div1.parent = &root;
    div2.parent = &root;
    div3.parent = &root;
    div4.parent = &root;
    div5.parent = &root;
    div6.parent = &root;
    div7.parent = &root;
    div8.parent = &root;
    div9.parent = &root;

    div1.next = &div2;
    div2.next = &div3;
    div3.next = &div4;
    div4.next = &div5;
    div5.next = &div6;
    div6.next = &div7;
    div7.next = &div8;
    div8.next = &div9;

    root.child = &div1;

    t2Renderer *renderer = t2Renderer::getInstance();
    t2LayoutController* layoutController = t2LayoutController::getInstance();
    //renderer->loadFont("mono", "../resources/font/Roboto-Regular.ttf");
    renderer->setFont("mono");

    t2DivController *divController = t2DivController::getInstance();
    divController->addDiv("div3", &div3);
    divController->addDiv("div2", &div2);
    divController->addDiv("div1", &div1); 
    divController->addDiv("root", &root);
    divController->addDiv("div4", &div4);
    divController->addDiv("div5", &div5);
    divController->addDiv("div6", &div6);
    divController->addDiv("div7", &div7);
    divController->addDiv("div8", &div8);
    divController->addDiv("div9", &div9);

    divController->setRoot("root");

    divController->init();

    layoutController->updateAll();

    float i = 0;

    while(1)
    {
        renderer->clear(210, 210, 210);

        renderer->begin();
        
        layoutController->update();

        divController->draw();

        renderer->end();

        window->swapBuffer();

        window->processEvents();
    }

    return 0;
}