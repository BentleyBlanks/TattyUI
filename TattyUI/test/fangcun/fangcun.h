#include <TattyUI/test/fangcun/fcTattyUI.h>

// fc
float rayX, rayY;

fcRay *r = NULL;

fcController *c = NULL;

t2Vector2f* intersect = NULL;

void init()
{
    initCommon();

    // ray
    rayX = rand() % 800 + 200;
    rayY = rand() % 700 + 50;
    r = new fcRay(rayX, rayY, 0, 0);

    // circle
    c = fcController::getInstace();

    for(int i = 0; i < 200; i++)
    {
        float x = rand() % 1280;
        float y = rand() % 700 + 50;
        float radius = rand() % 20 + 10;

        c->addCircle(new fcCircle(x, y, radius));
    }
}

void timing()
{
    // test speed
    timer.start();

    intersect = c->intersection(*r);

    timer.end();

    t2Log("cost time: %lf\n", timer.difference());
}

int main()
{    
    init();

    timing();

    while(1)
    {
        begin();

        r->set(rayX, rayY, t2GetMouseX(), t2GetMouseY());

        r->draw();

        c->draw();

        intersect = c->intersection(*r);

        if(intersect)
        {
            renderer->setColor(50, 50, 211, 255);
            renderer->drawCircle(intersect->x, intersect->y, 2, true);
        }

        end();
    }
    
    getchar();
    return 0;
}
